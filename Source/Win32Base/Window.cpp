//! @file Win32Base/Window.cpp
//! @brief The definition of an object which wraps a handle to a top-level
//! window.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/Window.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object representing a top-level window which is not
//! bound to a window resource.
Window::Window() :
    BaseWindow()
{
}

//! @brief Constructs an object representing a top-level window which is bound
//! to a window resource.
//! @param[in] handle The handle of the window resource to bind to.
Window::Window(HWND handle) :
    BaseWindow(handle)
{
}

//! @brief Sets the display mode of the window.
//! @param[in] showMode The new display mode, such as SW_SHOWMAXIMIZED, etc.
//! @retval true The window was previously visible.
//! @retval false The window was previously hidden.
bool Window::show(int showMode) const
{
    HWND handle = getHandle();
    bool wasVisible = false;

    if (handle != nullptr)
    {
        wasVisible = ::ShowWindow(handle, showMode) != FALSE;
    }

    return wasVisible;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////

