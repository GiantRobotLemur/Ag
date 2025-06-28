//! @file Ag/Win32Base/Ctrl.hpp
//! @brief The declaration of an object which wraps a handle to a child window.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_CTRL_HPP__
#define __AG_WIN32_BASE_CTRL_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../Core/Configuration.hpp"
#include "../Core/String.hpp"
#include "BaseWindow.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which wraps a handle to a child window.
class Ctrl : public BaseWindow
{
public:
    // Construction/Destruction
    Ctrl();
    Ctrl(HWND handle);
    Ctrl(const BaseWindow &childWindow);

    // Accessors

    // Operations
    bool setVisible(bool isVisible);
    bool attachCtrl(const BaseWindow &parent, uint32_t id);
protected:
    // Internal Functions
    void createCtrl(HWND parentHandle, wchar_cptr_t className,
                    const RECT &posAndSize, uint32_t style, uint32_t id,
                    const String &text);
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
