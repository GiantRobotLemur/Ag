//! @file Win32Base/InternalTools.cpp
//! @brief The definition of various tools not exposed as part of the library API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include "InternalTools.hpp"
#include "Ag/Win32Base/Tools.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Modaliser Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an object which disables the owner window and shows the
//! dialog window.
//! @param[in] ownerHandle The handle to the owner window.
//! @param[in] dialogHandle The handle to the hidden dialog window to show.
//! @param[in] isModal An optional pointer to a flag to set to true for the
//! lifetime of the object.
Modaliser::Modaliser(HWND ownerHandle, HWND dialogHandle, bool *isModal) :
    OwnerHandle(ownerHandle),
    OwnerEnableState(FALSE),
    IsModal(isModal)
{
    if (IsModal)
        *IsModal = true;

    if ((OwnerHandle == ::GetDesktopWindow()) ||
        (OwnerHandle == HWND_DESKTOP))
    {
        OwnerHandle = nullptr;
    }

    if (::IsWindow(ownerHandle))
    {
        OwnerEnableState = ::IsWindowEnabled(ownerHandle);

        // Prevent input being received by the parent window.
        ::EnableWindow(ownerHandle, FALSE);

        // Position the window above its owner.
        ::SetWindowPos(dialogHandle, ownerHandle, 0, 0, 0, 0,
                       SWP_NOMOVE | SWP_NOSIZE);
    }

    // Display the window.
    ::ShowWindow(dialogHandle, SW_NORMAL);
}

//! @brief Ensures the owner window is re-enabled and the IsModal flag is reset
//! to false if it was defined.
Modaliser::~Modaliser()
{
    if (IsModal)
        *IsModal = false;

    if (::IsWindow(OwnerHandle))
    {
        // Determine if the owner window was previously visible.
        bool wasVisible = ::IsWindowVisible(OwnerHandle) != FALSE;

        // Re-enable input to the parent window.
        ::EnableWindow(OwnerHandle, OwnerEnableState);

        if (wasVisible && (OwnerHandle != nullptr))
        {
            // Raise the owner window.
            ::SetActiveWindow(OwnerHandle);
        }
    }
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
