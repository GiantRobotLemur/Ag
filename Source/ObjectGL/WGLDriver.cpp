//! @file ObjectGL/WGLDriver.cpp
//! @brief The definition of an object which uses direct calls to the WGL API
//! to create an OpenGL context.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "DisplayContextPrivate.hpp"
#include "RenderContextPrivate.hpp"

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/ObjectGL/APIResolvers.hpp"
#include "Ag/ObjectGL/ContextOptions.hpp"
#include "Ag/ObjectGL/DisplayFormat.hpp"
#include "Ag/ObjectGL/WGL_Tools.hpp"
#include "Ag/ObjectGL/WGLDriver.hpp"
#include "Ag/ObjectGL/WGL_CommandSets.hpp"
#include "Ag/ObjectGL/Extensions/ARB.hpp"

namespace gl {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
class WGLDisplayContextPrivate;
using WGLDisplayContextPrivateSPtr = std::shared_ptr<WGLDisplayContextPrivate>;

//! @brief An implementation of RenderContextPrivate which uses the WGL API.
class WGLRenderContextPrivate : public RenderContextPrivate
{
private:
    // Internal Fields
    HWND _window;
    HDC _device;
    HGLRC _glContext;

    // Internal Functions
    WGLDisplayContextPrivateSPtr getParent();
public:
    // Construction/Destruction
    WGLRenderContextPrivate(const std::shared_ptr<DisplayContextPrivate> &display,
                            HWND window, HDC device, HGLRC context);

    virtual ~WGLRenderContextPrivate();

    // Accessors
    HWND getWindow() const { return _window; }
    HDC getDevice() const { return _device; }
    HGLRC getContext() const { return _glContext; }

    // Overrides
    virtual void makeCurrent() override;
    virtual void doneCurrent() override;
    virtual void swapBuffers() override;
};

//! @brief An implementation of DisplayContextPrivate which uses the WGL API.
class WGLDisplayContextPrivate : public DisplayContextPrivate
{
private:
    // Internal Fields
    wgl::WGLResolver _resolver;
    DisplayFormat _format;
    std::shared_ptr<WGLRenderContextPrivate> _rootContext;
    wgl::WGL _wglAPI;
    gl::GL _glAPI;
    wgl::ARBCreateContext _createContextAPI;
    Ag::Version _maxSupportedVersion;
    int _pixelFormatID;

    // Internal Functions
    static LRESULT CALLBACK primitiveGLWinProc(HWND handle, UINT id,
                                               WPARAM wParam, LPARAM lParam);
    static HWND createHiddenOpenGLWindow(bool allowErrors);
    static void mapPixelFormatProperties(const DisplayFormat &format,
                                         std::vector<int> &intProps);
    static void mapContextProperties(const ContextOptions &options,
                                     bool noVersion, std::vector<int> &intProps);
    HGLRC WGLDisplayContextPrivate::createLegacyOpenGLContext(HDC device,
                                                              const DisplayFormat &format) const;
public:
    // Construction/Destruction
    WGLDisplayContextPrivate(const DisplayFormat &format);

    virtual ~WGLDisplayContextPrivate() = default;

    // Accessors
    const wgl::WGL getWGL_API() const { return _wglAPI; }

    // Operations
    void initialiseRootContext();

    // Overrides
    virtual const Ag::Version &getMaxSupportedCoreVersion() const override { return _maxSupportedVersion; }
    virtual const APIResolver *getResolver() const override { return &_resolver; }
    virtual RenderContextPrivateSPtr createContext(uintptr_t drawable,
                                                   const ContextOptions &options) override;
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// WGLRenderContextPrivate Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets the parent WGL display.
WGLDisplayContextPrivateSPtr WGLRenderContextPrivate::getParent()
{
    auto parent = getDisplay();

    return std::dynamic_pointer_cast<WGLDisplayContextPrivate>(parent);
}

//! @brief Constructs an object encapsulating a modern WGL OpenGL context.
//! @param[in] display The display object which owns the context.
//! @param[in] window The window associated with the context.
//! @param[in] device The GDI device associated with the context.
//! @param[in] context The modern OpenGL context to manage.
WGLRenderContextPrivate::WGLRenderContextPrivate(
        const std::shared_ptr<DisplayContextPrivate> &display,
        HWND window, HDC device, HGLRC context) :
    RenderContextPrivate(display),
    _window(window),
    _device(device),
    _glContext(context)
{
}

//! @brief Ensures that the encapsulated OpenGL context is not selected and then
//! properly disposed of, along with the associated device context.
WGLRenderContextPrivate::~WGLRenderContextPrivate()
{
    auto parent = getParent();
    const auto &wgl = parent->getWGL_API();

    if (wgl.wglGetCurrentContext() == _glContext)
    {
        wgl.wglMakeCurrent(nullptr, nullptr);
    }

    wgl.wglDeleteContext(_glContext);
    _glContext = nullptr;

    if (_device != nullptr)
    {
        ::ReleaseDC(_window, _device);
        _device = nullptr;
    }
}

// Inherited from RenderContextPrivate.
void WGLRenderContextPrivate::makeCurrent()
{
    const auto &wgl = getParent()->getWGL_API();

    if (wgl.wglMakeCurrent(_device, _glContext) == FALSE)
    {
        throw Ag::Win32Exception("wglMakeCurrent(OpenGL Context)", ::GetLastError());
    }
}

// Inherited from RenderContextPrivate.
void WGLRenderContextPrivate::doneCurrent()
{
    const auto &wgl = getParent()->getWGL_API();

    if (wgl.wglGetCurrentContext() == _glContext)
    {
        if (wgl.wglMakeCurrent(nullptr, nullptr) == FALSE)
        {
            throw Ag::Win32Exception("wglMakeCurrent(null)", ::GetLastError());
        }
    }
}

// Inherited from RenderContextPrivate.
void WGLRenderContextPrivate::swapBuffers()
{
    const auto &wgl = getParent()->getWGL_API();

    if (wgl.SwapBuffers(_device) == FALSE)
    {
        throw Ag::Win32Exception("SwapBuffers()", ::GetLastError());
    }
}

////////////////////////////////////////////////////////////////////////////////
// WGLDisplayContextPrivate Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief A call back function for a temporary window which does nothing.
//! @param[in] handle The handle of the window to process messages for.
//! @param[in] id The identifier of the message to process.
//! @param[in] wParam The word message parameter.
//! @param[in] lParam The long message parameter.
//! @return The result of processing the message.
LRESULT CALLBACK WGLDisplayContextPrivate::primitiveGLWinProc(
    HWND handle, UINT id, WPARAM wParam, LPARAM lParam)
{
    return ::DefWindowProcW(handle, id, wParam, lParam);
}

//! @brief Creates a temporary OpenGL-compatible window which is not displayed
//! and does nothing.
//! @param[in] allowErrors True to allow failures to throw an exception, otherwise
//! errors will merely return nullptr.
//! @returns A handle to the window, which it is up to the caller to destroy,
//! or nullptr if creation fails and @p allowErrors is true.
HWND WGLDisplayContextPrivate::createHiddenOpenGLWindow(bool allowErrors)
{
    static ATOM windowClassId = 0;

    if (windowClassId == 0)
    {
        WNDCLASSEXW wc;
        Ag::zeroFill(wc);
        wc.cbSize = sizeof(wc);
        wc.lpszClassName = L"LegacyOpenGLWindow";
        wc.hInstance = ::GetModuleHandleW(nullptr);
        wc.lpfnWndProc = primitiveGLWinProc;
        wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);

        windowClassId = ::RegisterClassExW(&wc);

        if (windowClassId == 0)
        {
            if (allowErrors)
            {
                throw Ag::Win32Exception("RegisterClassEx(PrimitiveOpenGLWindow)",
                                         ::GetLastError());
            }
            else
            {
                return nullptr;
            }
        }
    }

    constexpr DWORD Style = WS_OVERLAPPEDWINDOW;
    constexpr DWORD StyleEx = WS_EX_OVERLAPPEDWINDOW;

    HWND handle = ::CreateWindowExW(StyleEx,
                                    reinterpret_cast<LPCWSTR>(windowClassId),
                                    nullptr, Style,
                                    CW_USEDEFAULT, CW_USEDEFAULT,
                                    100, 100,
                                    ::GetDesktopWindow(), nullptr,
                                    ::GetModuleHandleW(nullptr), nullptr);

    if ((handle == nullptr) && allowErrors)
    {
        throw Ag::Win32Exception("CreateWindowEx(PrimitiveOpenGLWindow)",
                                 ::GetLastError());
    }

    return handle;
}

//! @brief Maps generic display format properties to WGL-specific pixel format
//! attributes.
//! @param[in] format The set of generic properties to map.
//! @param[out] intProps The collection to encode the property values in.
void WGLDisplayContextPrivate::mapPixelFormatProperties(const DisplayFormat &format,
                                                        std::vector<int> &intProps)
{
    intProps.clear();
    intProps.reserve(32);

    intProps.push_back(wgl::Global::DrawToWindow);
    intProps.push_back(TRUE);
    intProps.push_back(wgl::Global::SupportOpenGL);
    intProps.push_back(TRUE);
    intProps.push_back(wgl::Global::PixelType);
    intProps.push_back(wgl::Global::TypeRGBA);

    bool flag = false;
    if (format.tryGetTypedProperty(DisplayPropertyID::HasHardwareAcceleration, flag))
    {
        intProps.push_back(wgl::Global::Acceleration);
        intProps.push_back(flag ? wgl::Global::FullAcceleration : wgl::Global::NoAcceleration);
    }

    if (format.tryGetTypedProperty(DisplayPropertyID::HasDoubleBuffer, flag))
    {
        intProps.push_back(wgl::Global::DoubleBuffer);
        intProps.push_back(flag ? TRUE : FALSE);
    }

    int value = -1;
    if (format.tryGetTypedProperty(DisplayPropertyID::RedBitCount, value))
    {
        intProps.push_back(wgl::Global::RedBits);
        intProps.push_back(value);
    }

    if (format.tryGetTypedProperty(DisplayPropertyID::GreenBitCount, value))
    {
        intProps.push_back(wgl::Global::GreenBits);
        intProps.push_back(value);
    }

    if (format.tryGetTypedProperty(DisplayPropertyID::BlueBitCount, value))
    {
        intProps.push_back(wgl::Global::BlueBits);
        intProps.push_back(value);
    }

    if (format.tryGetTypedProperty(DisplayPropertyID::AlphaBitCount, value))
    {
        intProps.push_back(wgl::Global::AlphaBits);
        intProps.push_back(value);
    }

    if (format.tryGetTypedProperty(DisplayPropertyID::ColourBitCount, value))
    {
        intProps.push_back(wgl::Global::ColorBits);
        intProps.push_back(value);
    }

    if (format.tryGetTypedProperty(DisplayPropertyID::DepthBitCount, value))
    {
        intProps.push_back(wgl::Global::DepthBits);
        intProps.push_back(value);
    }

    if (format.tryGetTypedProperty(DisplayPropertyID::StencilBitCount, value))
    {
        intProps.push_back(wgl::Global::StencilBits);
        intProps.push_back(value);
    }

    // Terminate the attribute list.
    intProps.push_back(0);
}

//! @brief Maps generic context requirement properties to a set of WGL-specific
//! attributes.
//! @param[in] options The set of context requirements to map.
//! @param[in] noVersion True to ignore any OpenGL version requirement properties.
//! @param[out] intProps The collection to encode the property values in.
void WGLDisplayContextPrivate::mapContextProperties(const ContextOptions &options,
                                                    bool noVersion,
                                                    std::vector<int> &intProps)
{
    intProps.clear();
    intProps.reserve(8);
    int value = 0;

    if (noVersion == false)
    {
        if (options.tryGetTypedProperty(ContextPropertyID::MajorVersion, value))
        {
            intProps.push_back(wgl::Global::ContextMajorVersion);
            intProps.push_back(value);
        }

        if (options.tryGetTypedProperty(ContextPropertyID::MinorVersion, value))
        {
            intProps.push_back(wgl::Global::ContextMinorVersion);
            intProps.push_back(value);
        }
    }

    bool hasFlags = false;
    bool hasProfile = false;
    bool flag = false;

    GLuint flags = 0;
    GLuint profile = 0;

    if (options.tryGetTypedProperty(ContextPropertyID::UseCoreProfile, flag))
    {
        hasProfile = true;
        profile |= flag ? wgl::Global::ContextCoreProfile : 0;
    }

    if (options.tryGetTypedProperty(ContextPropertyID::UseCompatabilityProfile, flag))
    {
        hasProfile = true;
        profile |= flag ? wgl::Global::ContextCompatibilityProfile : 0;
    }

    if (options.tryGetTypedProperty(ContextPropertyID::UseESProfile, flag))
    {
        hasProfile = true;
        profile |= flag ? wgl::Global::ContextES2Profile : 0;
    }

    if (options.tryGetTypedProperty(ContextPropertyID::UseForwardCompatiblity, flag))
    {
        hasFlags = true;
        flags |= flag ? wgl::Global::ContextForwardCompatible : 0;
    }

    if (options.tryGetTypedProperty(ContextPropertyID::EnableDebugging, flag))
    {
        hasFlags = true;
        flags |= flag ? wgl::Global::ContextDebug : 0;
    }

    if (hasFlags)
    {
        intProps.push_back(wgl::Global::ContextFlags);
        intProps.push_back(flags);
    }

    if (hasProfile)
    {
        intProps.push_back(wgl::Global::ContextProfileMask);
        intProps.push_back(profile);
    }

    // Terminate the list.
    intProps.push_back(0);
}

//! @brief Creates a legacy OpenGL context which can be used to resolve entry
//! points for creation of a more modern context.
//! @param[in] device The context of the device to create the OpenGL context on.
//! @param[in] format Details of the display format the OpenGL context should support.
//! @return A handle to an OpenGL context.
HGLRC WGLDisplayContextPrivate::createLegacyOpenGLContext(HDC device,
                                                          const DisplayFormat &format) const
{
    PIXELFORMATDESCRIPTOR formatInfo;
    Ag::zeroFill(formatInfo);
    formatInfo.nSize = sizeof(formatInfo);
    formatInfo.nVersion = 1;
    formatInfo.iPixelType = PFD_TYPE_RGBA;
    formatInfo.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    formatInfo.iLayerType = PFD_MAIN_PLANE;

    if (format.tryGetTypedProperty(DisplayPropertyID::DepthBitCount,
                                   formatInfo.cDepthBits) == false)
    {
        formatInfo.dwFlags |= PFD_DEPTH_DONTCARE;
    }

    formatInfo.dwFlags |= format.getProperty(DisplayPropertyID::HasHardwareAcceleration,
                                             true) ? PFD_GENERIC_ACCELERATED : 0;

    bool useDoubleBuffer = false;

    if (format.tryGetTypedProperty(DisplayPropertyID::HasDoubleBuffer, useDoubleBuffer))
    {
        if (useDoubleBuffer)
        {
            formatInfo.dwFlags |= PFD_DOUBLEBUFFER;
        }
    }
    else
    {
        formatInfo.dwFlags |= PFD_DOUBLEBUFFER_DONTCARE;
    }

    // Note: The following work because we know that the formatInfo fields start
    // off as zero.
    int bpp = ::GetDeviceCaps(device, BITSPIXEL);
    formatInfo.cColorBits = format.getTypedValue(DisplayPropertyID::ColourBitCount, static_cast<BYTE>(bpp));
    formatInfo.cAlphaBits = format.getTypedValue(DisplayPropertyID::AlphaBitCount, static_cast<BYTE>(0));

    // Not required for ChoosePixelFormat();
    //formatInfo.cDepthBits = format.getTypedValue(DisplayPropertyID::DepthBitCount, formatInfo.cDepthBits);
    //formatInfo.cStencilBits = format.getTypedValue(DisplayPropertyID::DepthBitCount, formatInfo.cStencilBits);

    int formatId = _wglAPI.ChoosePixelFormat(device, &formatInfo);

    if (formatId == 0)
    {
        throw Ag::Win32Exception("ChoosePixelFormat()", ::GetLastError());
    }

    PIXELFORMATDESCRIPTOR chosenFormat;
    Ag::zeroFill(chosenFormat);
    chosenFormat.nSize = sizeof(chosenFormat);

    if (_wglAPI.DescribePixelFormat(device, formatId, sizeof(chosenFormat), &chosenFormat) == 0)
    {
        throw Ag::Win32Exception("DescribePixelFormat()", ::GetLastError());
    }

    if (_wglAPI.SetPixelFormat(device, formatId, &chosenFormat) == FALSE)
    {
        throw Ag::Win32Exception("SetPixelFormat()", ::GetLastError());
    }

    HGLRC glContext = _wglAPI.wglCreateContext(device);

    if (glContext == nullptr)
    {
        throw Ag::Win32Exception("wglCreateContext()", ::GetLastError());
    }

    return glContext;
}

//! @brief Constructs an object which can create OpenGL contexts from a
//! shared source.
//! @param[in] format The display format required by the new context.
WGLDisplayContextPrivate::WGLDisplayContextPrivate(const DisplayFormat &format) :
    _resolver(true),
    _format(format),
    _pixelFormatID(0)
{
}

//! @brief Ensures that a root context is initialised.
void WGLDisplayContextPrivate::initialiseRootContext()
{
    if (_rootContext)
        return;

    // Create a window and device context with which to create a legacy OpenGL
    // context (OpenGL 1.1).
    HWND window = createHiddenOpenGLWindow(true);
    Ag::AtScopeExit1 destroyLegacyWindow(DestroyWindow, window);
    HDC legacyDevice = ::GetDC(window);
    Ag::AtScopeExit2 releaseLegacyDC(::ReleaseDC, window, legacyDevice);

    _wglAPI.resolveEntryPoints(&_resolver);

    HGLRC legacyContext = createLegacyOpenGLContext(legacyDevice, _format);
    Ag::AtScopeExit1 deleteLegacyContext(_wglAPI.wglDeleteContext, legacyContext);
    wgl::ARBPixelFormat pixelFormatAPI;
    auto makeCurrent = _wglAPI.wglMakeCurrent;

    if (makeCurrent(legacyDevice, legacyContext) == FALSE)
    {
        throw Ag::Win32Exception("wglMakeCurrent(Legacy OpenGL Context)", ::GetLastError());
    }
    else
    {
        // Ensure we de-select the legacy context at scope exit.
        Ag::AtScopeExit doneLegacyContext([makeCurrent]() {
                                           makeCurrent(nullptr, nullptr); });

        _resolver.setDevice(legacyDevice);

        if (_resolver.isExtensionPresent("WGL_ARB_create_context") &&
            _resolver.isExtensionPresent("WGL_ARB_pixel_format"))
        {
            _createContextAPI.resolveEntryPoints(&_resolver);
            pixelFormatAPI.resolveEntryPoints(&_resolver);
        }
        else
        {
            throw Ag::NotSupportedException("Modern OpenGL context creation.");
        }
    }

    // We can't create a modern context with the same Window/DC, so disposed of
    // the old ones and create new ones.
    deleteLegacyContext.exec();
    releaseLegacyDC.exec();
    destroyLegacyWindow.exec();

    window = createHiddenOpenGLWindow(true);
    Ag::AtScopeExit1 destroyRootWindow(::DestroyWindow, window);
    HDC modernDevice = ::GetDC(window);
    Ag::AtScopeExit2 releaseModernDC(::ReleaseDC, window, modernDevice);

    std::vector<int> intProps;
    int formatId = -1;
    UINT formatCount = 0;

    mapPixelFormatProperties(_format, intProps);

    if (pixelFormatAPI.wglChoosePixelFormat(modernDevice, intProps.data(), nullptr,
                                            1, &formatId, &formatCount) == FALSE)
    {
        throw Ag::Win32Exception("wglChoosePixelFormatARB()", ::GetLastError());
    }
    else if (formatCount < 1)
    {
        throw Ag::OperationException("No matching pixel formats found.");
    }

    // Get full details of the pixel format chosen.
    PIXELFORMATDESCRIPTOR formatInfo;
    Ag::zeroFill(formatInfo);
    formatInfo.nSize = sizeof(formatInfo);
    formatInfo.nVersion = 1;

    if (_wglAPI.DescribePixelFormat(modernDevice, formatId,
                                    sizeof(formatInfo), &formatInfo) == 0)
    {
        throw Ag::Win32Exception("DescribPixelFormat()", ::GetLastError());
    }

    // Set the pixel format on our root window/DC.
    if (_wglAPI.SetPixelFormat(modernDevice, formatId, &formatInfo) == FALSE)
    {
        throw Ag::Win32Exception("SetPixelFormat()", ::GetLastError());
    }

    // Create a context for the root window.
    ContextOptions options;
    options.enableCoreProfile(true);

    mapContextProperties(options, true, intProps);
    HGLRC modernContext = _createContextAPI.wglCreateContextAttribs(modernDevice, nullptr,
                                                                    intProps.data());

    if (modernContext == nullptr)
    {
        throw Ag::Win32Exception("wglCreateContextAttribs()",
                                 ::GetLastError());
    }

    Ag::AtScopeExit1 deleteModernContext(_wglAPI.wglDeleteContext, modernContext);

    if (makeCurrent(modernDevice, modernContext) == FALSE)
    {
        throw Ag::Win32Exception("wglMakeCurrent(Modern OpenGL Context)",
                                 ::GetLastError());
    }

    // Ensure we de-select the current OpenGL context at exit.
    Ag::AtScopeExit doneModernContext([makeCurrent]() { makeCurrent(nullptr, nullptr); });

    _pixelFormatID = formatId;
    _resolver.setDevice(modernDevice);
    _createContextAPI.resolveEntryPoints(&_resolver);

    DisplayContextPrivate::initialiseAPI();

    // Get the maximum version supported by the context.
    auto &api = getAPI();
    api.getAPIVersion();
    GLint major = 0, minor = 0;
    api.getIntegerV(GetPName::MajorVersion, &major);
    api.getIntegerV(GetPName::MinorVersion, &minor);

    // Try to retain the comment in the version.
    _maxSupportedVersion = api.getAPIVersion();

    if (major != 0)
        _maxSupportedVersion.setMajor(static_cast<uint16_t>(major));

    if (minor != 0)
        _maxSupportedVersion.setMinor(static_cast<uint16_t>(minor));

    deleteModernContext.cancel();
    releaseModernDC.cancel();
    destroyRootWindow.cancel();

    _rootContext = std::make_shared<WGLRenderContextPrivate>(shared_from_this(),
                                                             window,
                                                             modernDevice,
                                                             modernContext);

    // Ensure the root context has a resolved API.
    _rootContext->initialiseAPI(&_resolver);

    // De-select the context and retain it for future use.
    makeCurrent(nullptr, nullptr);
}

// Inherited from DisplayContextPrivate.
RenderContextPrivateSPtr WGLDisplayContextPrivate::createContext(uintptr_t drawable,
                                                                 const ContextOptions &options)
{
    HWND drawableHandle = reinterpret_cast<HWND>(drawable);

    if (::IsWindow(drawableHandle) == FALSE)
        throw Ag::ArgumentException("The drawable value is not a valid window handle.",
                                    "drawable");

    if (!_rootContext)
        throw Ag::OperationException("The display context has no root OpenGL context to share.");

    HDC drawableDC = ::GetDC(drawableHandle);
    Ag::AtScopeExit2 releaseDrawableDC(::ReleaseDC, drawableHandle, drawableDC);

    std::vector<int> intProps;

    mapPixelFormatProperties(_format, intProps);

    // Get full details of the pixel format chosen.
    PIXELFORMATDESCRIPTOR formatInfo;
    Ag::zeroFill(formatInfo);
    formatInfo.nSize = sizeof(formatInfo);
    formatInfo.nVersion = 1;

    if (_wglAPI.DescribePixelFormat(drawableDC, _pixelFormatID,
                                    sizeof(formatInfo), &formatInfo) == 0)
    {
        throw Ag::Win32Exception("DescribPixelFormat()", ::GetLastError());
    }

    // Set the pixel format on our root window/DC.
    if (_wglAPI.SetPixelFormat(drawableDC, _pixelFormatID, &formatInfo) == FALSE)
    {
        throw Ag::Win32Exception("SetPixelFormat()", ::GetLastError());
    }

    // Create a context for the root window.
    mapContextProperties(options, false, intProps);

    HGLRC renderContext = _createContextAPI.wglCreateContextAttribs(drawableDC,
                                                                    _rootContext->getContext(),
                                                                    intProps.data());

    if (renderContext == nullptr)
    {
        throw Ag::Win32Exception("wglCreateContextAttribs()",
                                 ::GetLastError());
    }

    // Ensure the context is deleted if an exception is thrown creating the wrapper.
    Ag::AtScopeExit1 deleteContext(_wglAPI.wglDeleteContext, renderContext);

    auto renderer = std::make_shared<WGLRenderContextPrivate>(shared_from_this(),
                                                              drawableHandle,
                                                              drawableDC,
                                                              renderContext);

    deleteContext.cancel();
    releaseDrawableDC.cancel();

    // Ensure the context has access to all appropriate functions.
    renderer->makeCurrent();
    renderer->initialiseAPI(&_resolver);
    renderer->doneCurrent();

    return renderer;
}

////////////////////////////////////////////////////////////////////////////////
// WGLDriver Member Definitions
////////////////////////////////////////////////////////////////////////////////
// Inherited from IDriver.
DisplayContext WGLDriver::createDisplayDevice(const DisplayFormat &format) const
{
    std::shared_ptr<WGLDisplayContextPrivate> context = std::make_shared<WGLDisplayContextPrivate>(format);

    // Has to be done as a second step after construction.
    context->initialiseRootContext();

    return AssignableDisplayContext(context);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////



