//! @file Win32Base/Ctrl.cpp
//! @brief The definition of an object which wraps a handle to a child window.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Win32Base/Win32API.hpp"
#include "Ag/Win32Base/Ctrl.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object wrapping a child window which is not bound to a
//! window resource.
Ctrl::Ctrl() :
    BaseWindow()
{
}

//! @brief Constructs an object wrapping a child window which is bound to a
//! window resource.
//! @param[in] handle The handle of the child window resource to bind to.
Ctrl::Ctrl(HWND handle) :
    BaseWindow(handle)
{
}

//! @brief Constructs an object wrapping a resource which is bound to a
//! child window.
//! @param[in] childWindow The child window instance.
Ctrl::Ctrl(const BaseWindow &childWindow) :
    BaseWindow(childWindow.getHandle())
{
}

//! @brief Sets the visibility state of the control.
//! @param[in] isVisible True to make the control visible, false to hide it.
//! @retval true The control was previously visible.
//! @retval false The control was previously hidden.
bool Ctrl::setVisible(bool isVisible)
{
    HWND handle = getHandle();
    bool wasVisible = false;

    if (handle != nullptr)
    {
        wasVisible = ::ShowWindow(handle, isVisible ? SW_NORMAL : SW_HIDE) != FALSE;
    }

    return wasVisible;
}

//! @brief Attaches the object to an existing dialog control.
//! @param[in] parent The parent window which hosts the control.
//! @param[in] id The numeric identifier of the control.
//! @retval true The control was successfully bound to the current object.
//! @retval false The control did not exist or the parent was invalid.
bool Ctrl::attachCtrl(const BaseWindow &parent, uint32_t id)
{
    if (parent.isBound())
    {
        HWND handle = ::GetDlgItem(parent.getHandle(), static_cast<int>(id));

        if (handle != nullptr)
        {
            attach(handle);
            return true;
        }
    }

    return false;
}

//! @brief Creates a control and attaches it to the object.
//! @param[in] parentHandle The handle representing the window the control should
//! be added to.
//! @param[in] className The name of the control type.
//! @param[in] posAndSize The position and size in pixels relative to the origin
//! of the parent windows's client area.
//! @param[in] style The style of the control such as WS_VISIBLE and ES_MULTILINE.
//! @param[in] id The numeric identifier of the control.
//! @param[in] text The initial text displayed in the control.
void Ctrl::createCtrl(HWND parentHandle, wchar_cptr_t className,
                      const RECT &posAndSize, uint32_t style, uint32_t id,
                      const String &text)
{
    std::wstring buffer;
    Utf::appendToWide(buffer, text.getUtf8Bytes(), text.getUtf8Length(),
                      text.getWideLength());
    HINSTANCE moduleHandle = reinterpret_cast<HINSTANCE>(::GetWindowLongPtrW(parentHandle, GWLP_HINSTANCE));

    HWND handle = ::CreateWindowExW(0, className, buffer.c_str(), style | WS_CHILD,
                                    posAndSize.left, posAndSize.top,
                                    posAndSize.right - posAndSize.left,
                                    posAndSize.bottom - posAndSize.top,
                                    parentHandle, reinterpret_cast<HMENU>(static_cast<uintptr_t>(id)),
                                    moduleHandle, nullptr);

    if (handle == nullptr)
    {
        throw Win32Exception("CreateWindowEx(Ctrl)", ::GetLastError());
    }
    else
    {
        attach(handle);
    }
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////

