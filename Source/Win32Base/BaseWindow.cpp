//! @file Win32Base/BaseWindow.cpp
//! @brief The definition of an object wrapping a handle of a any window.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/App.hpp"
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/Win32Base/BaseWindow.hpp"
#include "Ag/Win32Base/Message.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object not bound to an underlying window resource.
BaseWindow::BaseWindow() :
    _handle(nullptr)
{
}

//! @brief Constructs an object bound to an underlying window resource.
//! @param[in] handle The handle of the window to bind the object to.
BaseWindow::BaseWindow(HWND handle) :
    _handle((IsWindow(handle) == 0) ? nullptr : handle)
{
}

//! @brief Determines if the object is bound to a valid window resource.
//! @retval true The object is bound to a window resource.
//! @retval false The object is unbound or the handle to the window resource
//! is invalid, perhaps because the window resource was destroyed since binding.
bool BaseWindow::isBound() const
{
    return (_handle != nullptr) && (::IsWindow(_handle) != FALSE);
}

//! @brief Gets the handle to the underlying window resource.
HWND BaseWindow::getHandle() const { return _handle; }

//! @brief Determines if the window is in a state where it is visible.
//! @retval true The window is in a visible state.
//! @retval false The window is in a hidden state.
bool BaseWindow::isVisible() const
{
    bool visible = false;

    if (_handle != nullptr)
    {
        visible = ::IsWindowVisible(_handle) != FALSE;
    }

    return visible;
}

//! @brief Determines whether the window is in an enabled state.
//! @retval true The window is enabled.
//! @retval false The window is disabled.
bool BaseWindow::isEnabled() const
{
    return (_handle != nullptr) && (::IsWindowEnabled(_handle) != FALSE);
}

//! @brief Sets the enabled state of the window.
//! @param[in] enabled True to enable the window, false to disable it.
void BaseWindow::setEnabled(bool enabled) const
{
    if (_handle != nullptr)
    {
        ::EnableWindow(_handle, enabled ? TRUE : FALSE);
    }
}

//! @brief Gets the current window style.
uint32_t BaseWindow::getStyle() const
{
    uint32_t style = 0;

    if (_handle != nullptr)
    {
        style = static_cast<uint32_t>(::GetWindowLongPtrW(_handle, GWL_STYLE));
    }

    return style;
}

//! @brief Gets the current window extended style.
uint32_t BaseWindow::getExStyle() const
{
    uint32_t style = 0;

    if (_handle != nullptr)
    {
        style = static_cast<uint32_t>(::GetWindowLongPtrW(_handle, GWL_EXSTYLE));
    }

    return style;
}

//! @brief Gets the size of the window client area in pixels.
SIZE BaseWindow::getClientSize() const
{
    SIZE cxy = { 0, 0 };

    if (_handle != nullptr)
    {
        RECT clientRect;

        if (::GetClientRect(_handle, &clientRect) != FALSE)
        {
            cxy.cx = clientRect.right - clientRect.left;
            cxy.cy = clientRect.bottom - clientRect.top;
        }
    }

    return cxy;
}

//! @brief Gets the client area as a rectangle.
RECT BaseWindow::getClientRect() const
{
    RECT clientArea = { 0, 0, 0, 0 };

    if (_handle != nullptr)
    {
        ::GetClientRect(_handle, &clientArea);
    }

    return clientArea;
}

//! @brief Gets the position and size of the window, in pixels, relative to the screen.
RECT BaseWindow::getWindowRect() const
{
    LegacyRect posAndSize;

    if (isBound())
    {
        ::GetWindowRect(_handle, &posAndSize);
    }

    return posAndSize;
}

//! @brief Calculates the window size given required client area dimensions.
//! @param[in] preferredClientSize The preferred size of the client area.
//! @return The window size which will create a client area of the specified size.
SIZE BaseWindow::calculateWindowSizeForClient(const SIZE &preferredClientSize) const
{
    SIZE windowSize = preferredClientSize;

    if (_handle != nullptr)
    {
        LegacyRect windowPlacement;
        windowPlacement.right = preferredClientSize.cx;
        windowPlacement.bottom = preferredClientSize.cy;

        if (::AdjustWindowRectExForDpi(&windowPlacement, getStyle(),
                                       (::GetMenu(_handle) == nullptr) ? FALSE : TRUE,
                                       getExStyle(), getDpi()))
        {
            windowSize = windowPlacement.getSize();
        }
    }

    return windowSize;
}

//! @brief Transforms a point from client coordinates to screen coordinates.
//! @param[in] clientPosition The position in client coordinates to transform.
//! @return The corresponding position in screen space.
POINT BaseWindow::clientToScreen(const POINT &clientPosition) const
{
    POINT transformed = clientPosition;

    if (isBound())
    {
        ::ClientToScreen(_handle, &transformed);
    }

    return transformed;
}

//! @brief Transforms a rectangle from client coordinates to screen coordinates.
//! @param[in] clientRect The rectangle in client coordinates to transform.
//! @return The corresponding rectangle in screen space.
RECT BaseWindow::clientToScreen(const RECT &clientRect) const
{
    RectI originalRect(clientRect);

    if (isBound())
    {
        PointI origin = originalRect.getOrigin();

        if (::ClientToScreen(_handle, &origin))
        {
            originalRect.setOrigin(origin);
        }
    }

    return originalRect.toLegacy();
}

//! @brief Translates a screen-relative position in pixels to a
//! client-relative position.
//! @param[in] screenPosition The position in screen pixels to translate.
//! @return The same position relative to the origin of the window's client area.
POINT BaseWindow::screenToClient(const POINT& screenPosition) const
{
    POINT transformed = screenPosition;

    if (isBound())
    {
        ::ScreenToClient(_handle, &transformed);
    }

    return transformed;
}

//! @brief Translates a screen-relative rectangle in pixels to a
//! client-relative rectangle.
//! @param[in] screenREct The rectangle in screen pixels to translate.
//! @return The same rectangle relative to the origin of the window's client area.
RECT BaseWindow::screenToClient(const RECT& screenRect) const
{
    RectI originalRect(screenRect);

    if (isBound())
    {
        PointI origin = originalRect.getOrigin();

        if (::ScreenToClient(_handle, &origin))
        {
            originalRect.setOrigin(origin);
        }
    }

    return originalRect.toLegacy();
}

//! @brief Gets the icon associated with a window.
//! @param[in] size The icon size, e.g. ICON_SMALL, ICON_BIG or ICON_SMALL2.
//! @return A handle to the icon or nullptr.
HICON BaseWindow::getIcon(uint32_t size /*= ICON_SMALL*/) const
{
    intptr_t handle = 0;

    if (isBound())
    {
        handle = sendMessage(WM_GETICON, static_cast<uintptr_t>(size), 0);
    }

    return reinterpret_cast<HICON>(handle);
}

//! @brief Sets the icon associated with a window.
//! @param[in] handle The handle of the icon to associate.
//! @param[in] size The icon size, e.g. ICON_SMALL, ICON_BIG or ICON_SMALL2.
//! @return A handle to the icon of the specified size previously set or nullptr.
HICON BaseWindow::setIcon(HICON handle, uint32_t size /*= ICON_SMALL*/) const
{
    intptr_t oldHandle = 0;

    if (isBound())
    {
        oldHandle = sendMessage(WM_SETICON, static_cast<uintptr_t>(size),
                                reinterpret_cast<intptr_t>(handle));
    }

    return reinterpret_cast<HICON>(oldHandle);
}


//! @brief Gets the current font used by the window.
HFONT BaseWindow::getFont() const
{
    return reinterpret_cast<HFONT>(::SendMessageW(_handle, WM_GETFONT, 0, 0));
}

//! @brief Gets the handle of the menu associated with the window.
HMENU BaseWindow::getMenu() const
{
    HMENU menu = nullptr;

    if (_handle != nullptr)
    {
        menu = reinterpret_cast<HMENU>(::GetMenu(_handle));
    }

    return menu;
}

//! @brief Sets the current font used by the window.
//! @param[in] fontHandle The handle to the new font.
//! @param[in] redrawOnChange True to redraw the window if the font is changed,
//! false to not redraw until the next scheduled WM_PAINT.
void BaseWindow::setFont(HFONT fontHandle, bool redrawOnChange /* = true */) const
{
    ::SendMessageW(_handle, WM_SETFONT, reinterpret_cast<WPARAM>(fontHandle),
                   redrawOnChange ? TRUE : FALSE);
}

//! @brief Gets the count of pixels per screen inch for the window on the
//! monitor it is currently displayed on.
uint32_t BaseWindow::getDpi() const
{
    uint32_t dpi = ::GetDpiForWindow(_handle);

    if (dpi == 0)
    {
        dpi = 96;
    }

    return dpi;
}

//! @brief Gets a system metrics property adjusted for the DPI scale of the
//! current window.
//! @param[in] propertyId The identifier of the property to obtain, such as SM_CXBORDER.
//! @return The value of the property appropriately scaled based on the DPI
//! scale of the window.
int BaseWindow::getSystemMetrics(int propertyId) const
{
    return ::GetSystemMetricsForDpi(propertyId, getDpi());
}

//! @brief Retrieves the value of one of the system-wide parameters, taking
//! into account the provided DPI value of the current window.
//! @param[in] uiAction The system-wide parameter to be retrieved such as
//! SPI_GETNONCLIENTMETRICS.
//! @param[in] uiParam A parameter whose usage and format depends on the
//! system parameter being queried.
//! @param[in,out] pvParam A parameter whose usage and format depends on 
//! the system parameter being queried.
//! @param[in] fWinIni If a system parameter is being set, specifies whether
//! the user profile is to be updated, and if so, whether the WM_SETTINGCHANGE
//! message is to be broadcast to all top-level windows to notify them of the
//! change. Valid could be 0 or SPIF_SENDCHANGE or others.
//! @return A boolean value indicating if the system parameter was properly
//! obtained or updated.
bool BaseWindow::getSystemParametersInfo(uint32_t uiAction, uint32_t uiParam,
                                         void *pvParam, uint32_t fWinIni /*= 0*/) const
{
    bool isOK = false;

    if (isBound() &&
        ((uiAction == SPI_GETICONTITLELOGFONT) ||
         (uiAction == SPI_GETICONMETRICS) ||
         (uiAction == SPI_GETNONCLIENTMETRICS)))
    {
        isOK = ::SystemParametersInfoForDpi(uiAction, uiParam, pvParam, fWinIni,
                                            ::GetDpiForWindow(_handle)) != FALSE;
    }
    else
    {
        isOK = ::SystemParametersInfoW(uiAction, uiParam, pvParam, fWinIni) != FALSE;
    }

    return isOK;
}

//! @brief Gets the handle of the module which owns the window class.
HINSTANCE BaseWindow::getOwnerModule() const
{
    HINSTANCE ownerHandle = nullptr;

    if (_handle == nullptr)
    {
        // Get the handle of the EXE module.
        ownerHandle = ::GetModuleHandleW(nullptr);
    }
    else
    {
        ownerHandle = reinterpret_cast<HINSTANCE>(::GetWindowLongPtrW(_handle, GWLP_HINSTANCE));
    }

    return ownerHandle;
}

//! @brief Posts a message to the window to be processed on the thread which
//! owns it for asynchronous processing.
//! @param[in] id The identifier of the message to send, such as WM_USER.
//! @param[in] wParam The word parameter specific to the message type.
//! @param[in] lParam The long parameter specific to the message type.
//! @throw Win32Exception If the message cannot be posted.
void BaseWindow::postMessage(uint32_t id, uintptr_t wParam, intptr_t lParam) const
{
    if (::PostMessageW(_handle, id, wParam, lParam) == FALSE)
    {
        throw Win32Exception("PostMessage()", ::GetLastError());
    }
}

//! @brief Sends a message to the window for synchronous processing.
//! @param[in] id The identifier of the message to send, such as WM_USER.
//! @param[in] wParam The word parameter specific to the message type.
//! @param[in] lParam The long parameter specific to the message type.
//! @returns The result of processing the message.
intptr_t BaseWindow::sendMessage(uint32_t id, uintptr_t wParam, intptr_t lParam) const
{
    return ::SendMessageW(_handle, id, wParam, lParam);
}

//! @brief Gets the value of a window instance property.
//! @param[in] index The index of the property to get, such as GWLP_HINSTANCE
//! @return The value of the property or 0.
intptr_t BaseWindow::getLongValue(int index) const
{
    intptr_t value = 0;

    if (isBound())
    {
        value = ::GetWindowLongPtrW(_handle, index);
    }

    return value;
}

//! @brief Gets the value of a window class property.
//! @param[in] index The index of the property to get, such as GCLP_HICON
//! @return The value of the property or 0.
intptr_t BaseWindow::getClassLongValue(int index) const
{
    intptr_t value = 0;

    if (isBound())
    {
        value = ::GetWindowLongPtrW(_handle, index);
    }

    return value;
}


//! @brief Sets the position and size of the window within its parent.
//! @param[in] posAndSize The rectangle representing the new window position
//! and size in pixels relative to the client area of the parent.
//! @param[in] flags Bits to pass to SetWindowPos(), SWP_NOZORDER and
//! SWP_NOOWNERZORDER will be automatically applied.
void BaseWindow::setPosition(const RECT &posAndSize,
                             uint32_t flags /* = SWP_NOACTIVATE */) const
{
    if (_handle != nullptr)
    {
        if (::SetWindowPos(_handle, nullptr, posAndSize.left, posAndSize.top,
                           posAndSize.right - posAndSize.left,
                           posAndSize.bottom - posAndSize.top,
                           SWP_NOZORDER | SWP_NOOWNERZORDER | flags) == FALSE)
        {
            throw Win32Exception("SetWindowPos()", ::GetLastError());
        }
    }
}

//! @brief Gets the text stored in a window as an immutable UTF-8 string.
Ag::String BaseWindow::getText() const
{
    std::vector<wchar_t> buffer;

    int len = getUnicodeText(buffer);

    return (len > 0) ? String(buffer.data(), static_cast<size_t>(len)) :
                       String::Empty;
}

//! @brief Determines if the window has text set without obtaining it.
bool BaseWindow::hasText() const
{
    return ::GetWindowTextLengthW(_handle) > 0;
}

//! @brief Sets the text which appears in the window, possibly the title bar.
//! @param[in] text The text expressed as an immutable UTF-8 string.
void BaseWindow::setText(const Ag::String &text) const
{
    std::wstring buffer = text.toWide();

    ::SetWindowTextW(_handle, buffer.c_str());
}

//! @brief Sets the text which appears in the window, possibly the title bar.
//! @param[in] text The text expressed as a wide character string.
void BaseWindow::setText(const std::wstring &text) const
{
    ::SetWindowTextW(_handle, text.c_str());
}

//! @brief Gets the Unicode characters of the text in the window.
//! @param[out] buffer The buffer to receive the null-terminated characters.
//! @return The count of characters stored in buffer, not including any
//! terminating null characters.
//! @note The buffer size will definitely be greater than the returned
//! length value.
int BaseWindow::getUnicodeText(std::vector<wchar_t> &buffer) const
{
    buffer.clear();
    int length = ::GetWindowTextLengthW(_handle);

    if (length > 0)
    {
        buffer.resize(static_cast<size_t>(length) + 1, L'\0');

        length = ::GetWindowTextW(_handle, buffer.data(),
                                  static_cast<int>(buffer.size()));
    }

    return length;
}

//! @brief Gets the current position of a built-in scroll bar.
//! @param[in] isVertical True to retrieve the position of the vertical built-in
//! scroll bar, false for the position of the horizontal bar.
//! @return The offset in units defined by the scroll bar.
int BaseWindow::getScrollPos(bool isVertical) const
{
    SCROLLINFO info;
    info.cbSize = sizeof(info);
    info.fMask = SIF_POS;

    return (::GetScrollInfo(_handle,
                            isVertical ? SB_VERT : SB_HORZ,
                            &info) == FALSE) ? 0 : info.nPos;
}

//! @brief Gets information about the current state of a built-in scroll
//! bar built to the current window.
//! @param[in] isVertical True to retrieve information from the vertical built-in
//! scroll bar, false for information from the horizontal bar.
//! @param[out] info The structure to fill in, which does not need to be
//! initialised in any way.
bool BaseWindow::getScrollInfo(bool isVertical, SCROLLINFO &info) const
{
    Ag::zeroFill(info);
    info.cbSize = sizeof(info);
    info.fMask = SIF_ALL;

    return ::GetScrollInfo(_handle, isVertical ? SB_VERT : SB_HORZ, &info) != FALSE;
}

//! @brief Updates the current state of a built-in scroll bar.
//! @param[in] isVertical True to set information on the vertical built-in
//! scroll bar, false to set information on the horizontal bar.
//! @param[in] info A structure defining the updated information along with
//! flags set in the fMask field defining which values should be updated.
//! @param[in] redraw Indicates if the scroll bar should be redrawn to show
//! its updated state.
//! @returns The new position of the affected scroll bar.
int BaseWindow::setScrollInfo(bool isVertical, const SCROLLINFO &info,
                               bool redraw /*= true*/) const
{
    return ::SetScrollInfo(_handle, isVertical ? SB_VERT : SB_HORZ,
                           &info, redraw ? TRUE : FALSE);
}

//! @brief Destroys the window resource, unbinding it from the current object
//! internally.
void BaseWindow::destroy() const
{
    if (_handle != nullptr)
    {
        if (::DestroyWindow(_handle) == FALSE)
        {
            throw Win32Exception("DestroyWindow()", ::GetLastError());
        }
    }
}

//! @brief Asynchronously schedules the entire client area of the window for
//! repainting.
//! @param[in] eraseBackground True to erase the background when BeginPaint()
//! is called when processing WM_PAINT, false to leave it in tact.
void BaseWindow::invalidate(bool eraseBackground /* = true */) const
{
    if (_handle != nullptr)
    {
        if (::InvalidateRect(_handle, nullptr, eraseBackground ? TRUE : FALSE) == FALSE)
        {
            throw Win32Exception("InvalidateRect(NoRect)", ::GetLastError());
        }
    }
}

//! @brief Asynchronously schedules part of the client area of the window for
//! repainting.
//! @param[in] area The area of the window to repaint in client coordinates.
//! @param[in] eraseBackground True to erase the background when BeginPaint()
//! is called when processing WM_PAINT, false to leave it in tact.
void BaseWindow::invalidateRect(const RECT &area, bool eraseBackground /* = true */) const
{
    if (_handle != nullptr)
    {
        if (::InvalidateRect(_handle, &area, eraseBackground ? TRUE : FALSE) == FALSE)
        {
            throw Win32Exception("InvalidateRect(Rect)", ::GetLastError());
        }
    }
}

//! @brief Synchronously sends a WM_PAINT message to the window for any areas
//! marked as invalid.
void BaseWindow::update() const
{
    if (_handle != nullptr)
    {
        if (::UpdateWindow(_handle) == FALSE)
        {
            throw Win32Exception("UpdateWindow()", ::GetLastError());
        }
    }
}

//! @brief Associates the object with a specified window resource.
//! @param[in] handle The handle of the window resource to attach to.
void BaseWindow::attach(HWND handle)
{
    // Only allow valid handles to be set.
    if ((handle != nullptr) && (::IsWindow(handle) != FALSE))
    {
        _handle = handle;
    }
    else
    {
        _handle = nullptr;
    }
}

//! @brief Registers a class which will call processMessage() on the
//! BaseWindow-derived object passed to CreateWindowEx().
//! @param[in] windowType The description of the window type to register.
//! @returns The atom value which represents the registered class.
//! @throws Win32Exception if class registration failed.
ATOM BaseWindow::registerClass(const WNDCLASSEXW &windowType)
{
    WNDCLASSEXW editedType = windowType;

    if (editedType.hInstance == nullptr)
    {
        // Use the handle of the root EXE module.
        editedType.hInstance = ::GetModuleHandleW(nullptr);
    }

    editedType.lpfnWndProc = reinterpret_cast<WNDPROC>(messageCallback);

    ATOM classRef = ::RegisterClassExW(&editedType);

    if (classRef == 0)
    {
        // Capture the error before doing things which might reset it.
        uint32_t errorCode = ::GetLastError();

        std::string fnName("RegisterClassEx(");

        if (isValidAddress(windowType.lpszClassName))
        {
            Utf::appendWide(fnName, windowType.lpszClassName,
                            std::wcslen(windowType.lpszClassName));
        }

        fnName.push_back(')');

        throw Win32Exception(fnName.c_str(), errorCode);
    }

    return classRef;
}

//! @brief Gets the handle of the module which contains the window procedure
//! used by BaseWindow-derived object to process messages.
HINSTANCE BaseWindow::getCallbackOwnerModule()
{
    static HINSTANCE ownerModuleHandle = nullptr;

    if (ownerModuleHandle == nullptr)
    {
        // Look up the module handle from the address of the function.
        if (::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                 GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                 reinterpret_cast<LPWSTR>(BaseWindow::messageCallback),
                                 &ownerModuleHandle) == FALSE)
        {
            throw Win32Exception("GetModuleHandleEx(BaseWindow::messageCallback)",
                                 ::GetLastError());
        }
    }

    return ownerModuleHandle;
}

//! @brief An internal callback function which can be used to bind a window
//! resource to a BaseWindow-derived object an call processMessage() to process
//! message received by the window.
//! @param[in] handle The handle of the window the message was sent to.
//! @param[in] msgId The identifier of the message, such as WM_CREATE.
//! @param[in] wParam The word parameter, specific to the message type.
//! @param[in] lParam The long parameter, specific to the message type.
//! @returns The result of processing the message, possibly produced by default
//! message processing.
intptr_t BaseWindow::messageCallback(HWND handle, uint32_t msgId,
                                     intptr_t wParam, uintptr_t lParam)
{
    Message message(handle, msgId, wParam, lParam);
    BaseWindow *obj = nullptr;

    if ((msgId == WM_CREATE) || (msgId == WM_NCCREATE))
    {
        // The window is being created, bind it to the object.
        LPCREATESTRUCTW windowParams;

        if (message.tryGetLongParamPtr(windowParams) &&
            isValidAddress(windowParams->lpCreateParams))
        {
            obj = static_cast<BaseWindow *>(windowParams->lpCreateParams);

            if (obj->_handle == nullptr)
            {
                // Bind the object and the window resource together.
                obj->_handle = handle;
                ::SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(obj));
            }
        }
    }

    if (obj == nullptr)
    {
        obj = reinterpret_cast<BaseWindow *>(::GetWindowLongPtrW(handle, GWLP_USERDATA));
    }

    if (obj != nullptr)
    {
        try
        {
            // Use the object to process the message.
            obj->processMessage(message);
        }
        catch (const Ag::Exception &error)
        {
            App *theApp = App::get();

            if (theApp)
            {
                theApp->onUnhandledException(error);
            }

            if ((msgId == WM_CREATE) || (msgId == WM_NCCREATE))
            {
                // Ensure window creation fails.
                message.setResult(-1);
            }
        }
    }

    // Perform default processing if necessary.
    intptr_t result;
    if (message.tryGetResult(result) == false)
    {
        result = ::DefWindowProcW(handle, msgId, wParam, lParam);
    }

    // If the window is being destroyed, unbind it from the window.
    if ((msgId == WM_DESTROY) || (msgId == WM_NCDESTROY))
    {
        if (obj != nullptr)
        {
            // Break the connection between the object and the window resource.
            obj->_handle = nullptr;
        }
    }

    return result;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////

