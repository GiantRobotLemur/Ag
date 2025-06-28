//! @file Ag/Win32Base/MessageBox.hpp
//! @brief The declaration of a class which allows modal message box
//! functionality to be properly integrated with the thread Dispatcher object.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_MESSAGE_BOX_HPP__
#define __AG_WIN32_BASE_MESSAGE_BOX_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseWindow.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A class which allows modal message box functionality to be properly
//! integrated with the thread Dispatcher object.
namespace MsgBox
{
    //! @brief Defines buttons which might appear in a message box.
    enum Button : uint32_t
    {
        None = 0x0000,
        OK = 0x0001,
        Cancel = 0x0002,
        TryAgain = 0x0004,
        Abort = 0x0008,
        Retry = 0x0010,
        Ignore = 0x0020,
        Yes = 0x0040,
        No = 0x0080,

        Mask = 0x00FF,
    };

    //! @brief Defines the icon to display in a message box.
    enum class Icon : uint8_t
    {
        //! @brief Synonymous with MB_ICONINFORMATION and MB_ICONASTERISK.
        Information,

        //! @brief Synonymous with MB_ICONWARNING and MB_ICONEXCLAMATION.
        Warning,

        //! @brief Synonymous with MB_ICONSTOP, MB_ICONERROR and MB_ICONHAND.
        Error,

        //! @brief Synonymous with MB_ICONQUESTION.
        Question,

        //! @brief Displays the IDI_SHIELD standard icon.
        Shield,
    };

    Button show(const BaseWindow &owner,
                Ag::string_cref_t message, Ag::string_cref_t title,
                uint32_t buttons, Icon icon,
                MsgBox::Button defaultButton = MsgBox::None);

    Button show(HWND ownerHandle,
                Ag::string_cref_t message, Ag::string_cref_t title,
                uint32_t buttons, Icon icon,
                MsgBox::Button defaultButton = MsgBox::None);

} // namespace MsgBox

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
