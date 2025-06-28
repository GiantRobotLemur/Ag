//! @file Ag/Win32Base/BaseWindow.hpp
//! @brief The declaration of an object wrapping a handle of a any window.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_BASE_WINDOW_HPP__
#define __AG_WIN32_BASE_BASE_WINDOW_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <vector>

#include "Win32API.hpp"
#include "Ag/Core/String.hpp"
#include "MessageTarget.hpp"

namespace Ag {

//! @brief A namespace encapsulating objects specifically built on top of the
//! Win32 API.
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class Message;

//! @brief An object wrapping a handle of a any window.
class BaseWindow : public MessageTarget
{
public:
    // Construction/Destruction
    BaseWindow();
    BaseWindow(HWND handle);
    virtual ~BaseWindow() = default;

    // Accessors
    bool isBound() const;
    HWND getHandle() const;
    bool isVisible() const;
    bool isEnabled() const;
    void setEnabled(bool enabled) const;
    uint32_t getStyle() const;
    uint32_t getExStyle() const;
    SIZE getClientSize() const;
    RECT getClientRect() const;
    RECT getWindowRect() const;
    SIZE calculateWindowSizeForClient(const SIZE &preferredClientSize) const;
    POINT clientToScreen(const POINT &clientPosition) const;
    RECT clientToScreen(const RECT &clientRect) const;
    POINT screenToClient(const POINT& screenPosition) const;
    RECT screenToClient(const RECT& screenRect) const;
    HICON getIcon(uint32_t size = ICON_SMALL) const;
    HICON setIcon(HICON handle, uint32_t size = ICON_SMALL) const;
    HMENU getMenu() const;
    HFONT getFont() const;
    void setFont(HFONT fontHandle, bool redrawOnChange = true) const;
    uint32_t getDpi() const;
    int getSystemMetrics(int propertyId) const;
    bool getSystemParametersInfo(uint32_t uiAction, uint32_t uiParam,
                                 void *pvParam, uint32_t fWinIni = 0) const;
    HINSTANCE getOwnerModule() const;
    void postMessage(uint32_t id, uintptr_t wParam, intptr_t lParam) const;
    intptr_t sendMessage(uint32_t id, uintptr_t wParam, intptr_t lParam) const;
    intptr_t getLongValue(int index) const;
    intptr_t getClassLongValue(int index) const;
    void setPosition(const RECT &posAndSize,
                     uint32_t flags = SWP_NOACTIVATE) const;
    Ag::String getText() const;
    bool hasText() const;
    void setText(const Ag::String &text) const;
    void setText(const std::wstring &text) const;
    int getUnicodeText(std::vector<wchar_t> &buffer) const;

    int getScrollPos(bool isVertical) const;
    bool getScrollInfo(bool isVertical, SCROLLINFO &info) const;
    int setScrollInfo(bool isVertical, const SCROLLINFO &info, bool redraw = true) const;

    // Operations
    void destroy() const;
    void invalidate(bool eraseBackground = true) const;
    void invalidateRect(const RECT &area, bool eraseBackground = true) const;
    void update() const;
protected:
    // Internal Functions
    void attach(HWND handle);
    static ATOM registerClass(const WNDCLASSEXW &windowType);
    static HINSTANCE getCallbackOwnerModule();
private:
    static intptr_t CALLBACK messageCallback(HWND handle, uint32_t msgId,
                                             intptr_t wParam, uintptr_t lParam);

    // Internal Fields
    HWND _handle;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
