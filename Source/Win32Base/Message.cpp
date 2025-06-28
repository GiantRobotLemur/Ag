//! @file Win32Base/Message.cpp
//! @brief The definition of an object representing a Win32 thread message.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/Message.hpp"

namespace Ag {

//! @brief A namespace containing Win32-specific element defined in the Ag
//! suite of libraries.
namespace Win32 {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief A union used to break a windows message parameter into 2 signed
//! 16-bit values.
union ParamPoint
{
    uintptr_t Parameter;
    int16_t Point[2];
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object representing an empty Windows message.
Message::Message() :
    _windowHandle(nullptr),
    _wordParameter(0u),
    _longParameter(0u),
    _messageId(WM_NULL)
{
}

//! @brief Constructs a window message to be processed.
//! @param[in] windowHandle The handle of the window the message is destined
//! for, nullptr for a thread message.
//! @param[in] messageId The message type, such as WM_CREATE or WM_DESTROY.
//! @param[in] wParam The word parameter the value of which is specific to
//! the message type.
//! @param[in] lParam The long parameter the value of which is specific to
//! the message type.
Message::Message(HWND windowHandle, uint32_t messageId,
                 uintptr_t wParam, intptr_t lParam) :
    _windowHandle(windowHandle),
    _wordParameter(wParam),
    _longParameter(lParam),
    _messageId(messageId)
{
}

//! @brief Constructs a window message to be processed.
//! @param[in] message A structure describing the message to process.
Message::Message(const MSG &message) :
    _windowHandle(message.hwnd),
    _wordParameter(message.wParam),
    _longParameter(message.lParam),
    _messageId(message.message)
{
}

//! @brief Gets the handle of the window the message is destined
//! for, nullptr for a thread message.
HWND Message::getWindowHandle() const { return _windowHandle; }

//! @brief Gets the message type, such as WM_CREATE or WM_DESTROY.
uint32_t Message::getMessageId() const { return _messageId; }

//! @brief Gets the word parameter the value of which is specific to
//! the message type.
uintptr_t Message::getWordParam() const { return _wordParameter.WordParam; }

//! @brief Gets the long parameter the value of which is specific to
//! the message type.
intptr_t Message::getLongParam() const { return _longParameter.LongParam; }

//! @brief Determines whether the message has been marked as handled.
//! @retval true The message has been handled and implicitly or explicitly
//! assigned a result.
//! @retval false The message has not been handled.
bool Message::isHandled() const { return _messageResult.has_value(); }

//! @brief Attempts to gets the value set as a result of processing the message.
//! @param[out] result Receives the result of processing the message.
//! @retval true The message was marked as handled.
//! @retval false The message was not marked as handled.
bool Message::tryGetResult(intptr_t &result) const
{
    if (_messageResult.has_value())
    {
        result = _messageResult.value();
        return true;
    }

    return false;
}

//! @brief Sets the message result and marks the message as handled.
//! @param[in] result The value to returns as a result of processing the message.
void Message::setResult(intptr_t result)
{
    _messageResult = result;
}

//! @brief Gets bits 0 to 15 of the word parameter.
uint32_t Message::getLowWordParameter() const
{
    return _wordParameter.Words[0];
}

//! @brief Gets bits 16-31 of the word parameter.
uint32_t Message::getHighWordParameter() const
{
    return _wordParameter.Words[1];
}

//! @brief Gets a position encoded in the lowest 32-bits of the word parameter.
POINT Message::getWordParameterPoint() const
{
    return { _wordParameter.Deltas[0], _wordParameter.Deltas[1] };
}

//! @brief Gets a size encoded as the first two unsigned 16-bit words of the
//! word parameter.
SIZE Message::getWordParameterSize() const
{
    return { _wordParameter.Words[0], _wordParameter.Words[1] };
}

//! @brief Gets bits 0 to 15 of the long parameter.
uint32_t Message::getLowLongParameter() const
{
    return _longParameter.Words[0];
}

//! @brief Gets bits 16-31 of the long parameter.
uint32_t Message::getHighLongParameter() const
{
    return _longParameter.Words[1];
}

//! @brief Gets a position encoded in the lowest 32-bits of the word parameter.
POINT Message::getLongParameterPoint() const
{
    return { _longParameter.Deltas[0], _longParameter.Deltas[1] };
}

//! @brief Gets a size encoded as the first two unsigned 16-bit words of the
//! long parameter.
SIZE Message::getLongParameterSize() const
{
    return { _longParameter.Words[0], _longParameter.Words[1] };
}

//! @brief Marks the message as handled and assigns an implicit result.
void Message::setHandled()
{
    _messageResult = 0;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////

