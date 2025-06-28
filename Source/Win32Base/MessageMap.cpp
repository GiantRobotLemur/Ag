//! @file Win32Base/MessageMap.cpp
//! @brief The definition of an object which dispatches a windows message to
//! the appropriate handler(s).
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

#include "Ag/Win32Base/BaseWindow.hpp"
#include "Ag/Win32Base/MessageMap.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// CommandMessage Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object representing the parameters of a WM_COMMAND message.
//! @param[in] message The raw WM_COMMAND Windows message to decode.
CommandMessage::CommandMessage(const Message &message) :
    _targetHandle(message.getWindowHandle()),
    _ctrlHandle(reinterpret_cast<HWND>(message.getLongParam())),
    _ctrlId(message.getLowWordParameter()),
    _notifyCode(message.getHighWordParameter())
{
}

//! @brief Gets the handle of the window the WM_COMMAND message was sent to.
HWND CommandMessage::getTargetHandle() const { return _targetHandle; }

//! @brief Gets the optional handle of the control the message references.
HWND CommandMessage::getCtrlHandle() const { return _ctrlHandle; }

//! @brief Gets the numeric identifier of the control which the command applied to.
uint32_t CommandMessage::getCtrlID() const { return _ctrlId; }

//! @brief Gets the code specifying the action which took place.
uint32_t CommandMessage::getNotifyCode() const { return _notifyCode; }

//! @brief Marks the message has handled.
void CommandMessage::setHandled() { _result = 0; }

//! @brief Makes the message as handled with a specific result.
//! @param[in] result The result of processing the command.
void CommandMessage::setResult(intptr_t result) { _result = result; }

//! @brief Transfers any result set to the original raw Windows message.
//! @param[in,out] message The message to update with a processing result, if any.
void CommandMessage::promoteResult(Message &message) const
{
    if (_result.has_value())
    {
        message.setResult(_result.value());
    }
}

////////////////////////////////////////////////////////////////////////////////
// NotifyMessage Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object providing the parameters of a WM_NOTIFY message.
//! @param[in] message The raw Windows message to decode.
NotifyMessage::NotifyMessage(const Message &message) :
    _notifyHeader(reinterpret_cast<LPNMHDR>(message.getLongParam())),
    _targetHandle(message.getWindowHandle())
{
}

//! @brief Gets the handle of the window the message was sent to for processing.
HWND NotifyMessage::getTargetHandle() const { return _targetHandle; }

//! @brief Gets the handle of the control which sent the message.
HWND NotifyMessage::getCtrlHandle() const { return _notifyHeader->hwndFrom; }

//! @brief Gets the numeric identifier of the control which sent the message.
uint32_t NotifyMessage::getCtrlID() const { return static_cast<uint32_t>(_notifyHeader->idFrom); }

//! @brief Gets the action the notification was created to indicate.
uint32_t NotifyMessage::getNotifyCode() const { return _notifyHeader->code; }

//! @brief Sets the message result to 0.
void NotifyMessage::setHandled() { _result = 0; }

//! @brief Sets the message result to a specific value.
//! @param[in] result The result of processing the notify message.
void NotifyMessage::setResult(intptr_t result) { _result = result; }

//! @brief Transfers any set result to the original raw Windows message.
//! @param[out] message The message to optionally update with a result.
void NotifyMessage::promoteResult(Message &message) const
{
    if (_result.has_value())
    {
        message.setResult(_result.value());
    }
}

////////////////////////////////////////////////////////////////////////////////
// MessageMap Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which can make numeric Windows message IDs to
//! member functions.
MessageMap::MessageMap() :
    _isMsgsOptimised(false),
    _isCmdOptimised(false),
    _isNotifyOptimised(false)
{
    _msgHandlers.reserve(16);
    _cmdHandlers.reserve(16);
}

//! @brief Adds a handler for a specific windows message.
//! @param[in] messageId The message identifier, such as WM_SIZE.
//! @param[in] target The object hosting which should process the message.
//! @param[in] fn A pointer to the member function to process the message.
void MessageMap::addHandler(uint32_t messageId, MessageTarget *target,
                            MessageMemberFnPtr fn)
{
    _isMsgsOptimised = _msgHandlers.empty();
    _msgHandlers.emplace_back(messageId, target, fn);
}

//! @brief Removes a handler for a specific windows message.
//! @param[in] messageId The identifier of the message the handler processes
//! such as WM_COMMAND.
//! @param[in] target The object hosting which should process the message.
//! @param[in] fn A pointer to the member function to process the message.
void MessageMap::removeHandler(uint32_t messageId, MessageTarget *target,
                               MessageMemberFnPtr fn)
{
    ensureMessagesOptimised();

    MsgHandler key(messageId, target, fn);
    auto resultPair = std::equal_range(_msgHandlers.begin(), _msgHandlers.end(), key);

    auto last = std::remove(resultPair.first, resultPair.second, key);

    _msgHandlers.erase(last, resultPair.second);
}

//! @brief Adds a handler for a WM_COMMAND message sent to a control.
//! @param[in] ctrlId The numeric identifier of the control.
//! @param[in] target The object hosting which should process the command.
//! @param[in] fn A pointer to the member function to process the command.
void MessageMap::addCommandHandler(uint32_t ctrlId, MessageTarget *target,
                                   CommandMemberFnPtr fn)
{
    _isCmdOptimised = _cmdHandlers.empty();
    _cmdHandlers.emplace_back(ctrlId, target, fn);
}

//! @brief Adds a handler for a WM_COMMAND message sent to a control.
//! @param[in] ctrlHandle The handle of the control.
//! @param[in] target The object hosting which should process the command.
//! @param[in] fn A pointer to the member function to process the command.
void MessageMap::addCommandHandler(HWND ctrlHandle, MessageTarget *target,
                                   CommandMemberFnPtr fn)
{
    if (ctrlHandle != nullptr)
    {
        _isCmdOptimised = _cmdHandlers.empty();
        _cmdHandlers.emplace_back(ctrlHandle, target, fn);
    }
}

//! @brief Adds a handler for a WM_COMMAND message sent to a control.
//! @param[in] ctrl The control which sent the message.
//! @param[in] target The object hosting which should process the command.
//! @param[in] fn A pointer to the member function to process the command.
void MessageMap::addCommandHandler(const BaseWindow &ctrl, MessageTarget *target,
                                   CommandMemberFnPtr fn)
{
    if (ctrl.isBound())
    {
        _isCmdOptimised = _cmdHandlers.empty();
        _cmdHandlers.emplace_back(ctrl.getHandle(), target, fn);
    }
}

//! @brief Removes a handler for a WM_COMMAND message sent to a control.
//! @param[in] ctrlId The numeric identifier of the control.
//! @param[in] target The object hosting which should process the command.
//! @param[in] fn A pointer to the member function to process the command.
void MessageMap::removeCommandHandler(uint32_t ctrlId, MessageTarget *target,
                                      CommandMemberFnPtr fn)
{
    ensureCommandsOptimised();

    CmdHandler key(ctrlId, target, fn);
    auto resultPair = std::equal_range(_cmdHandlers.begin(), _cmdHandlers.end(), key);

    auto last = std::remove(resultPair.first, resultPair.second, key);

    _cmdHandlers.erase(last, resultPair.second);
}

//! @brief Removes a handler for a WM_COMMAND message sent to a control.
//! @param[in] ctrlHandle The handle of the control.
//! @param[in] target The object hosting which should process the command.
//! @param[in] fn A pointer to the member function to process the command.
void MessageMap::removeCommandHandler(HWND ctrlHandle, MessageTarget *target,
                                      CommandMemberFnPtr fn)
{
    ensureCommandsOptimised();

    CmdHandler key(ctrlHandle, target, fn);
    auto resultPair = std::equal_range(_cmdHandlers.begin(), _cmdHandlers.end(), key);

    auto last = std::remove(resultPair.first, resultPair.second, key);

    _cmdHandlers.erase(last, resultPair.second);
}

//! @brief Removes a handler for a WM_COMMAND message sent to a control.
//! @param[in] ctrl The control which sent the message.
//! @param[in] target The object hosting which should process the command.
//! @param[in] fn A pointer to the member function to process the command.
void MessageMap::removeCommandHandler(const BaseWindow &ctrl, MessageTarget *target,
                                      CommandMemberFnPtr fn)
{
    if (ctrl.isBound())
    {
        ensureCommandsOptimised();

        CmdHandler key(ctrl.getHandle(), target, fn);
        auto resultPair = std::equal_range(_cmdHandlers.begin(), _cmdHandlers.end(), key);

        auto last = std::remove(resultPair.first, resultPair.second, key);

        _cmdHandlers.erase(last, resultPair.second);
    }
}

//! @brief Adds a handler for a WM_NOTIFY message.
//! @param[in] ctrlId The numeric identifier of the control.
//! @param[in] target The object hosting which should process the notification.
//! @param[in] fn A pointer to the member function to process the notification.
void MessageMap::addNotifyHandler(uint32_t ctrlId, MessageTarget *target,
                                  NotifyMemberFnPtr fn)
{
    _isNotifyOptimised = _notifyHandlers.empty();

    _notifyHandlers.emplace_back(static_cast<uintptr_t>(ctrlId), target, fn);
}

//! @brief Adds a handler for a WM_NOTIFY message.
//! @param[in] ctrlHandle The handle of the control.
//! @param[in] target The object hosting which should process the notification.
//! @param[in] fn A pointer to the member function to process the notification.
void MessageMap::addNotifyHandler(HWND ctrlHandle, MessageTarget *target,
                                  NotifyMemberFnPtr fn)
{
    _isNotifyOptimised = _notifyHandlers.empty();

    _notifyHandlers.emplace_back(ctrlHandle, target, fn);
}

//! @brief Adds a handler for a WM_NOTIFY message.
//! @param[in] ctrl The control which sent the notification.
//! @param[in] target The object hosting which should process the notification.
//! @param[in] fn A pointer to the member function to process the notification.
void MessageMap::addNotifyHandler(const BaseWindow &ctrl, MessageTarget *target,
                                  NotifyMemberFnPtr fn)
{
    if (ctrl.isBound())
    {
        _isNotifyOptimised = _notifyHandlers.empty();

        _notifyHandlers.emplace_back(ctrl.getHandle(), target, fn);
    }
}

//! @brief Removes a handler for a WM_NOTIFY message.
//! @param[in] ctrlId The numeric identifier of the control.
//! @param[in] target The object hosting which should process the notification.
//! @param[in] fn A pointer to the member function to process the notification.
void MessageMap::removeNotifyHandler(uint32_t ctrlId, MessageTarget *target,
                                     NotifyMemberFnPtr fn)
{
    ensureNotifyOptimised();

    NotifyHandler key(static_cast<uintptr_t>(ctrlId), target, fn);
    auto resultPair = std::equal_range(_notifyHandlers.begin(), _notifyHandlers.end(), key);

    auto last = std::remove(resultPair.first, resultPair.second, key);

    _notifyHandlers.erase(last, resultPair.second);
}

//! @brief Removes a handler for a WM_NOTIFY message.
//! @param[in] ctrlHandle The handle of the control.
//! @param[in] target The object hosting which should process the notification.
//! @param[in] fn A pointer to the member function to process the notification.
void MessageMap::removeNotifyHandler(HWND ctrlHandle, MessageTarget *target,
                                     NotifyMemberFnPtr fn)
{
    ensureNotifyOptimised();

    NotifyHandler key(reinterpret_cast<uintptr_t>(ctrlHandle), target, fn);
    auto resultPair = std::equal_range(_notifyHandlers.begin(), _notifyHandlers.end(), key);

    auto last = std::remove(resultPair.first, resultPair.second, key);

    _notifyHandlers.erase(last, resultPair.second);
}

//! @brief Removes a handler for a WM_NOTIFY message.
//! @param[in] ctrl The control which sent the notification.
//! @param[in] target The object hosting which should process the notification.
//! @param[in] fn A pointer to the member function to process the notification.
void MessageMap::removeNotifyHandler(const BaseWindow &ctrl, MessageTarget *target,
                                     NotifyMemberFnPtr fn)
{
    if (ctrl.isBound())
    {
        ensureNotifyOptimised();

        NotifyHandler key(ctrl.getHandle(), target, fn);
        auto resultPair = std::equal_range(_notifyHandlers.begin(), _notifyHandlers.end(), key);

        auto last = std::remove(resultPair.first, resultPair.second, key);

        _notifyHandlers.erase(last, resultPair.second);
    }
}

//! @brief Attempts to route the message to the appropriate handlers for
//! processing.
//! @param[in] message The message to process and the result of processing it.
void MessageMap::dispatch(Message &message)
{
    ensureMessagesOptimised();

    // Perform generic message handling.
    MsgHandler msgKey(message.getMessageId(), nullptr, nullptr);

    auto msgPair = std::equal_range(_msgHandlers.begin(),
                                    _msgHandlers.end(), msgKey);

    for (auto msgHandler = msgPair.first;
         msgHandler != msgPair.second;
         ++msgHandler)
    {
        (*msgHandler)(message);
    }

    if (message.getMessageId() == WM_COMMAND)
    {
        // Dispatch WM_COMMAND message to control-specific handlers.
        ensureCommandsOptimised();

        CommandMessage cmd(message);

        for (int i = 0; i < 2; ++i)
        {
            // Search by control ID and then handle.
            CmdHandler cmdIdKey((i == 0) ? static_cast<uintptr_t>(cmd.getCtrlID()) :
                                           reinterpret_cast<uintptr_t>(cmd.getCtrlHandle()),
                                nullptr, nullptr);

            auto cmdPair = std::equal_range(_cmdHandlers.begin(),
                                            _cmdHandlers.end(),
                                            cmdIdKey);

            for (auto cmdHandler = cmdPair.first;
                cmdHandler != cmdPair.second;
                ++cmdHandler)
            {
                (*cmdHandler)(cmd);
            }
        }

        // Transfer any result back to the original message.
        cmd.promoteResult(message);
    }
    else if (message.getMessageId() == WM_NOTIFY)
    {
        // Dispatch WM_NOTIFY message to control-specific handlers.
        ensureNotifyOptimised();

        NotifyMessage notify(message);

        // Try handling by numeric control ID, and then handle.
        for (int i = 0; i < 2; ++i)
        {
            NotifyHandler notifyKeyID(notify.getCtrlID(), nullptr, nullptr);

            if (i == 0)
            {
                if (notify.getCtrlID() == 0)
                    continue;
            }
            else
            {
                notifyKeyID = NotifyHandler(notify.getCtrlHandle(), nullptr, nullptr);
            }

            auto notifyPair = std::equal_range(_notifyHandlers.begin(),
                                               _notifyHandlers.end(),
                                               notifyKeyID);

            for (auto notifyHandler = notifyPair.first;
                notifyHandler != notifyPair.second;
                ++notifyHandler)
            {
                (*notifyHandler)(notify);
            }
        }

        // Transfer the result back to the original message.
        notify.promoteResult(message);
    }
}

//! @brief Ensures the message handler map is optimised for searching.
void MessageMap::ensureMessagesOptimised()
{
    if (_isMsgsOptimised == false)
    {
        std::sort(_msgHandlers.begin(), _msgHandlers.end());
        _isMsgsOptimised = true;
    }
}

//! @brief Ensures the command handler map is optimised for searching.
void MessageMap::ensureCommandsOptimised()
{
    if (_isCmdOptimised == false)
    {
        std::sort(_cmdHandlers.begin(), _cmdHandlers.end());
        _isCmdOptimised = true;
    }
}

//! @brief Ensures the notify handler map is optimised for searching.
void MessageMap::ensureNotifyOptimised()
{
    if (_isNotifyOptimised == false)
    {
        std::sort(_notifyHandlers.begin(), _notifyHandlers.end());
        _isNotifyOptimised = true;
    }
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
