//! @file Win32Base/CustomWindow.cpp
//! @brief The definition of an object which wraps a handle to a top-level
//! window and processes its messages.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include "Ag/Win32Base/Win32API.hpp"

#include "Ag/Core/String.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Core/Utils.hpp"
#include "Ag/Win32Base/CustomWindow.hpp"
#include "Ag/Win32Base/Message.hpp"
#include "Ag/Win32Base/Tools.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an unbound object representing a window resource for which
//! the object processes messages.
CustomWindow::CustomWindow() :
    Window(),
    _defaultFont(nullptr)
{
}

//! @brief Ensures that any bound window resource is destroyed.
CustomWindow::~CustomWindow()
{
    if (isBound())
    {
        // Destroy the window without throwing any exceptions.
        ::DestroyWindow(getHandle());
    }

    if (_defaultFont != nullptr)
    {
        ::DeleteObject(_defaultFont);
        _defaultFont = nullptr;
    }
}

//! @brief Gets the default UI font, scaled appropriately for DPI.
HFONT CustomWindow::getDefaultFont() const
{
    if (_defaultFont == nullptr)
    {
        // Lazily update the default font with the default message box font.
        NONCLIENTMETRICSW ncm;
        zeroFill(ncm);
        ncm.cbSize = sizeof(ncm);

        if (SystemParametersInfoForDpi(SPI_GETNONCLIENTMETRICS, ncm.cbSize,
                                       &ncm, 0, getDpi()))
        {
            _defaultFont = ::CreateFontIndirectW(&ncm.lfMessageFont);
        }
    }

    return (_defaultFont == nullptr) ? static_cast<HFONT>(::GetStockObject(DEFAULT_GUI_FONT)) :
                                       _defaultFont;
}

//! @brief Attempts to construct a new top-level window resource and bind it to
//! the current object.
//! @param[in] style The window style flags, such as WS_VISIBLE, WS_OVERLAPPED, etc.
//! @param[in] exStyle The extended style flags such as WS_EX_APPWINDOW.
//! @param[in] title The text to appear in the window title bar.
//! @param[in] position The optional position of the window origin point.
//! @param[in] size The optional dimensions of the window.
//! @param[in] menuHandle The optional handle of the window menu bar.
//! @param[in] ownerHandle The optional handle of the window which owns the
//! the one to be created.
//! @retval true The window was successfully created and bound to this object.
//! @retval false Either the object was already bound, window creation failed or
//! the new window was not successfully bound to this object.
bool CustomWindow::create(uint32_t style, uint32_t exStyle, const String &title,
                          PPOINT position /* = nullptr */,
                          PSIZE size /* = nullptr */,
                          HMENU menuHandle /* = nullptr */,
                          HWND ownerHandle /* = nullptr */)
{
    bool isOK = false;

    if (isBound() == false)
    {
        ATOM windowType = getRegisteredClass();
        int x = CW_USEDEFAULT,
            y = CW_USEDEFAULT,
            width = CW_USEDEFAULT,
            height = CW_USEDEFAULT;

        if (position != nullptr)
        {
            x = position->x;
            y = position->y;
        }

        if (size != nullptr)
        {
            width = size->cx;
            height = size->cy;
        }

        // Convert the window title to wide characters.
        std::wstring wideTitle;
        Utf::appendToWide(wideTitle, title.getUtf8Bytes(), title.getUtf8Length(),
                          title.getWideLength());

        uint32_t safeStyle = style & ~WS_CHILD;

        HWND safeOwner = ownerHandle;

        if (safeOwner == nullptr)
        {
            safeOwner = ::GetDesktopWindow();
        }

        HWND handle = ::CreateWindowExW(exStyle, makeResourceText(windowType),
                                        wideTitle.c_str(), safeStyle, x, y,
                                        width, height, safeOwner,
                                        menuHandle, getOwnerModule(),
                                        this);

        if (handle != nullptr)
        {
            isOK = isBound();
        }
    }

    return isOK;
}

//! @brief Performs some automatic message handling for DPI scale changes. This
//! function must be called if overridden in derived classes.
void CustomWindow::processMessage(Message &message)
{
    if (message.getMessageId() == WM_CREATE)
    {
        onCreate(message);
    }
    else if (message.getMessageId() == WM_DPICHANGED)
    {
        PRECT recommendedResize = nullptr;

        if (message.tryGetLongParamPtr(recommendedResize))
        {
            onDpiScaleChange(message.getLowWordParameter(),
                             message.getHighWordParameter(),
                             *recommendedResize);
            message.setHandled();
        }
    }

    Window::processMessage(message);
}

//! @brief A member function called before any other message processing
//! when the WM_CREATE message is processed.
//! @param[in] message Details of the message to process and the result of
//! processing it.
void CustomWindow::onCreate(Message &/*message*/)
{
}

//! @brief Called in response to the WM_DPICHANGED message.
//! @param[in] xDpi The new count of pixels per horizontal inch.
//! @param[in] yDpi The new count of pixels per vertical inch.
//! @param[in] recommendedResize The position and size of the window
//! adjusted for the new DPI scale.
//! @note The base implementation resizes the window to the recommended
//! rectangle.
void CustomWindow::onDpiScaleChange(uint32_t /* xDpi */, uint32_t /* yDpi */,
                                    const RECT &recommendedResize)
{
    if (_defaultFont != nullptr)
    {
        ::DeleteObject(_defaultFont);
        _defaultFont = nullptr;
    }

    ::SetWindowPos(getHandle(), nullptr, recommendedResize.left,
                   recommendedResize.top,
                   recommendedResize.right - recommendedResize.left,
                   recommendedResize.bottom - recommendedResize.top,
                   SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOZORDER);
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////

