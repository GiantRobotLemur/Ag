//! @file Ag/Win32Base/MessageTarget.hpp
//! @brief The declaration of an interface to an object which can process
//! Windows messages.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_MESSAGE_TARGET_HPP__
#define __AG_WIN32_BASE_MESSAGE_TARGET_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Message.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An interface to an object which can process Windows messages.
class MessageTarget
{
public:
    // Construction/Destruction
    MessageTarget() = default;
    virtual ~MessageTarget() = default;

protected:
    virtual void processMessage(Message &message);
};

//! @brief An alias for a pointer to a message handling member function on a
//! MessageTarget object.
typedef void (MessageTarget::*MessageMemberFnPtr)(Message &message);

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
