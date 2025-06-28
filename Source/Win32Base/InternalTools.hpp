//! @file Win32Base/InternalTools.hpp
//! @brief The declaration of various tools not exposed as part of the library API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_INTERNAL_TOOLS_HPP__
#define __AG_WIN32_BASE_INTERNAL_TOOLS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/Win32API.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An RAII utility class which displays a window, emulating modal
//! behaviour by disabling the owner window for the lifetime of the object.
struct Modaliser
{
    // Public Data
    HWND OwnerHandle;
    BOOL OwnerEnableState;
    bool *IsModal;

    // Construction/Destruction
    Modaliser(HWND ownerHandle, HWND dialogHandle, bool *isModal);
    ~Modaliser();
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
