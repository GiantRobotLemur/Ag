//! @file Win32Base/MessageTarget.cpp
//! @brief The definition of an interface to an object which can process
//! Windows messages.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/MessageTarget.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// MessageTarget Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Provides processing logic for a Windows message.
//! @param[in] message Details of the message to process.
void MessageTarget::processMessage(Message &/*message*/)
{
    // The base class does nothing.
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
