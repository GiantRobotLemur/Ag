//! @file Win32Base/CustomCtrl.cpp
//! @brief The definition of an object which wraps a child window and processes
//! its messages.
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

#include "Ag/Core/Utf.hpp"
#include "Ag/Win32Base/CustomCtrl.hpp"
#include "Ag/Win32Base/Tools.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an object not bound to an underlying child window.
CustomCtrl::CustomCtrl() :
    Ctrl()
{
}

//! @brief Ensure any bound child window is destroyed if not already.
CustomCtrl::~CustomCtrl()
{
    if (isBound())
    {
        // Destroy the window resource without throwing any exceptions.
        ::DestroyWindow(getHandle());
    }
}

//! @brief Create a child window resource and binds it to this object.
//! @param[in] parentHandle The handle of the parent window to create the
//! control within.
//! @param[in] posAndSize The position and size of the child window in pixels
//! relative to the parent window.
//! @param[in] style The window style flags, such as WS_VISIBLE. WS_CHILD will
//! be automatically applied.
//! @param[in] id The numeric identifier to attribute to the control.
//! @param[in] text The initial text displayed in the control.
//! @retval true The control was successfully created and bound to the object.
//! @retval false Either the object was already bound, creation failed or
//! the created control could not be bound.
bool CustomCtrl::create(HWND parentHandle, const RECT &posAndSize,
                        uint32_t style, uint32_t id /* = 0 */,
                        const String &text /* = String::Empty */)
{
    bool isOK = false;

    if (isBound() == false)
    {
        ATOM classRef = getRegisteredClass();

        if (classRef != 0)
        {
            // Convert the text to wide characters, if there is any.
            std::wstring buffer;

            Utf::appendToWide(buffer, text.getUtf8Bytes(),
                              text.getUtf8Length(),
                              text.getWideLength());

            // Create the window, which should call BaseWindow::messageCallback() to
            // process WM_CREATE which will bind the window handle to the
            // current object (passed as the lParam parameter below).
            HWND handle = ::CreateWindowExW(0, makeResourceText(classRef),
                                            buffer.c_str(), style | WS_CHILD,
                                            posAndSize.left, posAndSize.top,
                                            posAndSize.right - posAndSize.left,
                                            posAndSize.bottom - posAndSize.top,
                                            parentHandle,
                                            reinterpret_cast<HMENU>(static_cast<uintptr_t>(id)),
                                            getOwnerModule(), this);

            if (handle != nullptr)
            {
                // If all went well, the window procedure should have bound the
                // window handle to the object before returning.
                isOK = isBound();
            }
        }
    }

    return isOK;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////

