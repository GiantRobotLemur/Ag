//! @file Ag/Win32Base/Window.hpp
//! @brief The declaration of an object which wraps the handle to a top-level
//! window.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_WINDOW_HPP__
#define __AG_WIN32_BASE_WINDOW_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseWindow.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which wraps the handle to a top-level window.
class Window : public BaseWindow
{
public:
    // Construction/Destruction
    Window();
    Window(HWND handle);
    virtual ~Window() = default;

    // Operations
    bool show(int showMode) const;
private:
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
