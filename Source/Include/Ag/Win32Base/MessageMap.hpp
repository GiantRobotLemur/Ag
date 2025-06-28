//! @file Ag/Win32Base/MessageMap.hpp
//! @brief The declaration of an object which dispatches a windows message to
//! the appropriate handler(s).
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_MESSAGE_MAP_HPP__
#define __AG_WIN32_BASE_MESSAGE_MAP_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <optional>

#include "Message.hpp"
#include "MessageTarget.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#define MSG_HANDLER(x) reinterpret_cast<Ag::Win32::MessageMemberFnPtr>(&x)
#define CMD_HANDLER(x) reinterpret_cast<Ag::Win32::CommandMemberFnPtr>(&x)
#define NOTIFY_HANDLER(x) reinterpret_cast<Ag::Win32::NotifyMemberFnPtr>(&x)

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class BaseWindow;

//! @brief Details the parameters of a WM_COMMAND message.
class CommandMessage
{
public:
    // Construction/Destruction
    CommandMessage(const Message &message);
    ~CommandMessage() = default;

    // Accessors
    HWND getTargetHandle() const;
    HWND getCtrlHandle() const;
    uint32_t getCtrlID() const;
    uint32_t getNotifyCode() const;

    // Operations
    void setHandled();
    void setResult(intptr_t result);
    void promoteResult(Message &message) const;

private:
    // Internal Fields
    HWND _targetHandle;
    HWND _ctrlHandle;
    uint32_t _ctrlId;
    uint32_t _notifyCode;
    std::optional<intptr_t> _result;
};

typedef void (MessageTarget:: *CommandMemberFnPtr)(CommandMessage &message);

//! @brief Details the parameters of a WM_NOTIFY message.
class NotifyMessage
{
public:
    // Construction/Destruction
    NotifyMessage(const Message &message);
    ~NotifyMessage() = default;

    // Accessors
    HWND getTargetHandle() const;
    HWND getCtrlHandle() const;
    uint32_t getCtrlID() const;
    uint32_t getNotifyCode() const;

    template<typename TNotify>
    bool tryCastMessage(TNotify *&notifyStruct)
    {
        notifyStruct = reinterpret_cast<TNotify *>(_notifyHeader);

        return notifyStruct != nullptr;
    }

    // Operations
    void setHandled();
    void setResult(intptr_t result);
    void promoteResult(Message &message) const;

    // Operations

private:
    // Internal Fields
    LPNMHDR _notifyHeader;
    HWND _targetHandle;
    std::optional<intptr_t> _result;
};

typedef void (MessageTarget:: *NotifyMemberFnPtr)(NotifyMessage &message);

//! @brief An object which dispatches a windows message to the appropriate
//! handler(s).
class MessageMap
{
public:
    // Construction/Destruction
    MessageMap();
    ~MessageMap() = default;

    // Accessors

    // Operations
    void addHandler(uint32_t messageId, MessageTarget *target, MessageMemberFnPtr fn);
    void removeHandler(uint32_t messageId, MessageTarget *target, MessageMemberFnPtr fn);
    void addCommandHandler(uint32_t ctrlId, MessageTarget *target, CommandMemberFnPtr fn);
    void addCommandHandler(HWND ctrlHandle, MessageTarget *target, CommandMemberFnPtr fn);
    void addCommandHandler(const BaseWindow &ctrl, MessageTarget *target, CommandMemberFnPtr fn);
    void removeCommandHandler(uint32_t ctrlId, MessageTarget *target, CommandMemberFnPtr fn);
    void removeCommandHandler(HWND ctrlHandle, MessageTarget *target, CommandMemberFnPtr fn);
    void removeCommandHandler(const BaseWindow &ctrl, MessageTarget *target, CommandMemberFnPtr fn);
    void addNotifyHandler(uint32_t ctrlId, MessageTarget *target, NotifyMemberFnPtr fn);
    void addNotifyHandler(HWND ctrlHandle, MessageTarget *target, NotifyMemberFnPtr fn);
    void addNotifyHandler(const BaseWindow &ctrl, MessageTarget *target, NotifyMemberFnPtr fn);
    void removeNotifyHandler(uint32_t ctrlId, MessageTarget *target, NotifyMemberFnPtr fn);
    void removeNotifyHandler(HWND ctrlHandle, MessageTarget *target, NotifyMemberFnPtr fn);
    void removeNotifyHandler(const BaseWindow &ctrl, MessageTarget *target, NotifyMemberFnPtr fn);
    void dispatch(Message &message);
private:
    // Internal Type
    //! @brief A structure wrapping a message handler function pointer
    //! @tparam TMemberFnPtr The pointer-to-member-function type to wrap.
    template<typename TMemberFnPtr> struct Handler
    {
    private:
        uintptr_t _id;
        MessageTarget *_target;
        TMemberFnPtr _fn;
    public:
        //! @brief Constructs a new handler wrapper.
        //! @param[in] id The numeric identifier of the control which triggers
        //! the handler.
        //! @param[in] target The object on which the handler member function
        //! should be called.
        //! @param[in] fn The pointer to the member function to call.
        Handler(uintptr_t id, MessageTarget *target, TMemberFnPtr fn) :
            _target(target),
            _fn(fn),
            _id(id)
        {
        }

        //! @brief Constructs a new handler wrapper.
        //! @param[in] handle The handle of the child window which triggers
        //! the handler.
        //! @param[in] target The object on which the handler member function
        //! should be called.
        //! @param[in] fn The pointer to the member function to call.
        Handler(HWND handle, MessageTarget *target, TMemberFnPtr fn) :
            _target(target),
            _fn(fn),
            _id(reinterpret_cast<uintptr_t>(handle))
        {
        }

        //! @brief Gets the identifier of the control which triggers the handler.
        uintptr_t getId() const noexcept { return _id; }

        //! @brief Invokex the handler
        //! @tparam ...TArgs The types of the handler input parameters.
        //! @param ...args The handler argument values.
        template<typename ... TArgs>
        void operator()(TArgs && ... args) const
        {
            std::invoke(_fn, *_target, std::forward<TArgs>(args)...);
        }

        //! @brief Determines whether the handler matches another.
        //! @param[in] rhs The handler to compare against.
        //! @retval true If this handler matches @p rhs.
        //! @retval false If this handler is not a match for @p rhs.
        bool operator==(const Handler<TMemberFnPtr> &rhs) const noexcept
        {
            return (_target == rhs._target) &&
                (_fn == rhs._fn) &&
                (_id == rhs._id);
        }

        //! @brief A less-than comparison operator based on the window or
        //! control ID which triggers the handler.
        //! @param[in] rhs The handler to compare against.
        //! @retval true If the control identifier of handle targeted by the
        //! current handler has a lower value than that in @p rhs.
        //! @retval false If the control identifier is greater or equal to
        //! that in @p rhs.
        bool operator<(const Handler<TMemberFnPtr> &rhs) const noexcept
        {
            return (_id < rhs._id);
        }
    };

    using MsgHandler = Handler<MessageMemberFnPtr>;
    using MsgHandlerMap = std::vector<MsgHandler>;
    using MsgHandlerIter = MsgHandlerMap::iterator;

    using CmdHandler = Handler<CommandMemberFnPtr>;
    using CmdHandlerMap = std::vector<CmdHandler>;
    using CmdHandlerIter = CmdHandlerMap::iterator;

    using NotifyHandler = Handler<NotifyMemberFnPtr>;
    using NotifyHandlerMap = std::vector<NotifyHandler>;
    using NotifyHandlerIter = NotifyHandlerMap::iterator;

    // Internal Functions
    void ensureMessagesOptimised();
    void ensureCommandsOptimised();
    void ensureNotifyOptimised();

    // Internal Fields
    MsgHandlerMap _msgHandlers;
    CmdHandlerMap _cmdHandlers;
    NotifyHandlerMap _notifyHandlers;
    bool _isMsgsOptimised;
    bool _isCmdOptimised;
    bool _isNotifyOptimised;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
