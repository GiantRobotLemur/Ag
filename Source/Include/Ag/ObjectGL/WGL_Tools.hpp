//! @file Ag/ObjectGL/WGL_Tools.hpp
//! @brief The declaration of functions to assist using OpenGL on Windows.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_WGL_TOOLS_HPP__
#define __AG_OBJECT_GL_WGL_TOOLS_HPP__

// This stuff is only relevant if we're integrating with Windows.
#if defined _WIN32 && defined AG_OBJECT_GL_WGL_DRIVER

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <initializer_list>
#include <map>
#include <utility>

#include "APIResolvers.hpp"
#include "WGL_CommandSets.hpp"
#include "Extensions/AMDCommands.hpp"
#include "Extensions/ARBCommands.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Identifiers of properties which can be specified when describing
//! the rendering format of an OpenGL context yet to be created.
enum class FormatProperty : GLenum
{
    NumPixelFormat        = Global::NumberPixelFormats,     // WGL_NUMBER_PIXEL_FORMATS_ARB
    DrawToWindow          = Global::DrawToWindow,           // WGL_DRAW_TO_WINDOW_ARB
    DrawToBitmap          = Global::DrawToBitmap,           // WGL_DRAW_TO_BITMAP_ARB
    Acceleration          = Global::Acceleration,           // WGL_ACCELERATION_ARB
    NeedsPalette          = Global::NeedPalette,            // WGL_NEED_PALETTE_ARB
    NeedsSystemPalette    = Global::NeedSystemPalette,      // WGL_NEED_SYSTEM_PALETTE_ARB
    SwapLayerBuffers      = Global::SwapLayerBuffers,       // WGL_SWAP_LAYER_BUFFERS_ARB
    SwapMethod            = Global::SwapMethod,             // WGL_SWAP_METHOD_ARB
    NumOverlays           = Global::NumberOverlays,         // WGL_NUMBER_OVERLAYS_ARB
    NumUnderlays          = Global::NumberUnderlays,        // WGL_NUMBER_UNDERLAYS_ARB
    Transparent           = Global::Transparent,            // WGL_TRANSPARENT_ARB
    TransparentRedValue   = Global::TransparentRedValue,    // WGL_TRANSPARENT_RED_VALUE_ARB
    TransparentGreenValue = Global::TransparentGreenValue,  // WGL_TRANSPARENT_GREEN_VALUE_ARB
    TransparentBlueValue  = Global::TransparentBlueValue,   // WGL_TRANSPARENT_BLUE_VALUE_ARB
    TransparentAlphaValue = Global::TransparentAlphaValue,  // WGL_TRANSPARENT_ALPHA_VALUE_ARB
    TransparentIndexValue = Global::TransparentIndexValue,  // WGL_TRANSPARENT_INDEX_VALUE_ARB
    ShareDepth            = Global::ShareDepth,             // WGL_SHARE_DEPTH_ARB
    ShareStencil          = Global::ShareStencil,           // WGL_SHARE_STENCIL_ARB
    ShareAccum            = Global::ShareAccum,             // WGL_SHARE_ACCUM_ARB
    SupportGDI            = Global::SupportGDI,             // WGL_SUPPORT_GDI_ARB
    SupportOpenGL         = Global::SupportOpenGL,          // WGL_SUPPORT_OPENGL_ARB
    DoubleBuffer          = Global::DoubleBuffer,           // WGL_DOUBLE_BUFFER_ARB
    Stereo                = Global::Stereo,                 // WGL_STEREO_ARB
    PixelType             = Global::PixelType,              // WGL_PIXEL_TYPE_ARB
    ColorBits             = Global::ColorBits,              // WGL_COLOR_BITS_ARB
    RedBits               = Global::RedBits,                // WGL_RED_BITS_ARB
    RedShift              = Global::RedShift,               // WGL_RED_SHIFT_ARB
    GreenBits             = Global::GreenBits,              // WGL_GREEN_BITS_ARB
    GreenShift            = Global::GreenShift,             // WGL_GREEN_SHIFT_ARB
    BlueBits              = Global::BlueBits,               // WGL_BLUE_BITS_ARB
    BlueShift             = Global::BlueShift,              // WGL_BLUE_SHIFT_ARB
    AlphaBits             = Global::AlphaBits,              // WGL_ALPHA_BITS_ARB
    AlphaShift            = Global::AlphaShift,             // WGL_ALPHA_SHIFT_ARB
    AccumBits             = Global::AccumBits,              // WGL_ACCUM_BITS_ARB
    AccumRedBits          = Global::AccumRedBits,           // WGL_ACCUM_RED_BITS_ARB
    AccumGreenBits        = Global::AccumGreenBits,         // WGL_ACCUM_GREEN_BITS_ARB
    AccumBlueBits         = Global::AccumBlueBits,          // WGL_ACCUM_BLUE_BITS_ARB
    AccumAlphaBits        = Global::AccumAlphaBits,         // WGL_ACCUM_ALPHA_BITS_ARB
    DepthBits             = Global::DepthBits,              // WGL_DEPTH_BITS_ARB
    StencilBits           = Global::StencilBits,            // WGL_STENCIL_BITS_ARB
    AuxBuffers            = Global::AuxBuffers,             // WGL_AUX_BUFFERS_ARB
};

//! @brief Identifiers of properties which can be specified when creating a
//! modern OpenGL context.
enum class ContextProperty : GLenum
{
    MajorVersion = Global::ContextMajorVersion, // WGL_CONTEXT_MAJOR_VERSION_ARB
    MinorVersion = Global::ContextMinorVersion, // WGL_CONTEXT_MINOR_VERSION_ARB
    LayerPlane   = Global::ContextLayerPlane,   // WGL_CONTEXT_LAYER_PLANE_ARB
    Flags        = Global::ContextFlags,        // WGL_CONTEXT_FLAGS_ARB
    ProfileMask  = Global::ContextProfileMask,  // WGL_CONTEXT_PROFILE_MASK_ARB
};

//! @brief An object which defines properties within a specific schema.
//! @tparam TPropID The type defining the identifiers of properties to set.
//! @tparam TPropValue The data type of property values.
template<typename TPropID, typename TPropValue>
class PropertySet
{
public:
    // Public Types
    using ValueSet = std::vector<TPropValue>;
    using ValueMap = std::map<TPropID, TPropValue>;
private:
    std::map<TPropID, TPropValue> _properties;
public:
    // Construction/Destruction
    PropertySet() = default;
    ~PropertySet() = default;

    // Accessors
    //! @brief Gets the property values as an array of ID/value pairs,
    //! terminated a zero property ID.
    //! @returns A collection of ID/Value pairs all as value types.
    ValueSet getValues() const
    {
        ValueSet values;
        values.reserve((_properties.size() + 1) * 2);

        for (const auto &propPair : _properties)
        {
            values.push_back(static_cast<TPropValue>(propPair.first));
            values.push_back(propPair.second);
        }

        values.push_back(static_cast<TPropValue>(0));

        return values;
    }

    //! @brief Gets a value from the property set, using a default if it was
    //! not defined.
    //! @param[in] id The identifier of the property to look up.
    //! @param[in] defaultValue The value to return if the property was not
    //! defined.
    //! @return Ether the defined property value or defaultValue.
    TPropValue getValue(TPropID id, TPropValue defaultValue) const
    {
        auto pos = _properties.find(id);

        return (pos == _properties.end()) ? defaultValue : pos->second;
    }

    //! @brief Gets a value from the property set, converting its type. A
    //! default value will be returned if the property was not defined.
    //! @tparam T The data type to convert the property value to.
    //! @param[in] id The identifier of the property to look up.
    //! @param[in] defaultValue The value to return if the property was not
    //! defined.
    //! @return Ether the defined property value or defaultValue.
    template<typename T> T getTypedValue(TPropID id, T defaultValue) const
    {
        auto pos = _properties.find(id);

        return (pos == _properties.end()) ? defaultValue :
                                            static_cast<T>(pos->second);
    }

    //! @brief Attempts to get the value of a property, if it is defined.
    //! @param[in] id The identifier of the property to look up.
    //! @param[out] value Receives the value of the property, if defined.
    //! @retval true The property was defined and returned in value.
    //! @retval false The property was not defined, value is unmodified.
    bool tryGetValue(TPropID id, TPropValue &value) const
    {
        bool hasValue = false;

        auto pos = _properties.find(id);

        if (pos != _properties.end())
        {
            value = pos->second;
            hasValue = true;
        }

        return hasValue;
    }

    //! @brief Gets the mapping of property IDs to property values.
    const ValueMap &getMapping() const
    {
        return _properties;
    }

    // Operations
    //! @brief Defines a specified property, overwriting any previously set
    //! value with the same ID.
    //! @param[in] id The identifier of the property to set.
    //! @param[in] value The new value of the property.
    void defineProperty(TPropID id, TPropValue value)
    {
        _properties[id] = value;
    }
};

using PixelFormatIntAttribSet = PropertySet<FormatProperty, int>;
using PixelFormatFloatAttribSet = PropertySet<FormatProperty, float>;
using ContextAttribSet = PropertySet<ContextProperty, int>;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Resolves OpenGL entry points for use with a raw Win32 UI.
class WGLResolver : public APIResolver
{
public:
    // Construction/Destruction
    WGLResolver(bool loadOpenGL = false);
    virtual ~WGLResolver() = default;

    // Operations
    void setDevice(HDC device);

    // Overrides
    virtual bool isExtensionPresent(const char *extName) const override;
    virtual void *resolveEntryPoint(const char *fnName) const override;
    virtual APIResolver::GetNextErrorFn getErrorReporterProc() const override;
private:
    // Internal Types
    typedef PROC(WINAPI *GetProcAddrFn)(LPCSTR);

    // Internal Functions
    void initialise(bool loadOpenGL);

    template<typename T> bool resolve(const char *fnName, T &fnPtr) const
    {
        fnPtr = reinterpret_cast<T>(resolveEntryPoint(fnName));

        return fnPtr != nullptr;
    }

    // Internal Fields
    HMODULE _gdi32Dll;
    HMODULE _openGL32Dll;
    APIResolver::GetNextErrorFn _glGetError;
    GetProcAddrFn _getProcAddr;
    gl::ExtensionSet _extensions;
};

//! @brief An object which provides useful functions for working with OpenGL
//! on Windows.
class WGL_Tools
{
public:
    // Construction/Destruction
    WGL_Tools();

    // Accessors
    const APIResolver &getResolver() const;
    const WGLAPI &getWGL_API() const;
    const ARBCreateContextAPI &getContextCreationAPI() const;
    const ARBPixelFormatAPI &getPixelFormatAPI() const;
    const AMDGPUAssociationAPI &getGPUAssocAPI() const;

    // Operations
    void prepare(HDC device, HGLRC context);
    void prepare(HWND window, HGLRC context);
    void prepare(HWND displayWindow,
                 const PIXELFORMATDESCRIPTOR &preferredFormat);
    HGLRC createInitialContext(HWND window,
                               const PixelFormatIntAttribSet &intFormatProps,
                               const PixelFormatFloatAttribSet &floatFormatProps,
                               const ContextAttribSet &contextProps);
    HGLRC createSharedContext(HWND window, HGLRC shareContext,
                              const ContextAttribSet &contextProps);
private:
    // Internal Fields
    WGLResolver _resolver;
    WGLAPI _wgl;
    ARBCreateContextAPI _createContext;
    ARBPixelFormatAPI _pixelFormat;
    AMDGPUAssociationAPI _gpuAssociation;
    bool _isPrepared;
};

} // namespace wgl

#endif // if defined _WIN32 && defined AG_OBJECT_GL_WGL_DRIVER

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
