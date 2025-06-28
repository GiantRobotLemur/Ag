//! @file Ag/Win32Base/CustomCtrl.hpp
//! @brief The declaration of an object which wraps a child window and processes
//! its messages.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_CUSTOM_CTRL_HPP__
#define __AG_WIN32_BASE_CUSTOM_CTRL_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../Core/String.hpp"
#include "Ctrl.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which wraps a child window and processes its messages.
class CustomCtrl : public Ctrl
{
public:
    // Construction/Destruction
    CustomCtrl();
    virtual ~CustomCtrl();

    // Custom control instances cannot be copied.
    CustomCtrl(const CustomCtrl &) = delete;
    CustomCtrl(CustomCtrl &&) = delete;
    CustomCtrl &operator=(const CustomCtrl &) = delete;
    CustomCtrl &operator=(CustomCtrl &&) = delete;

    // Operations
    bool create(HWND parentHandle, const RECT &posAndSize, uint32_t style,
                uint32_t id = 0, const String &text = String::Empty);

protected:
    // Overrides
    //! @brief Lazily registers the window type so that instances can be created.
    //! @returns The atom representing the registered class.
    //! @details Implementations should have an ATOM static variable to keep
    //! track of the registration state and call BaseWindow::registerClass() in
    //! order to initialise it on first call.
    virtual ATOM getRegisteredClass() const = 0;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
