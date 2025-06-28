//! @file Ag/Win32Base/Dispatcher.hpp
//! @brief The declaration of an object which processes raw Win32 input messages
//! for a thread.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_DISPATCHER_HPP__
#define __AG_WIN32_BASE_DISPATCHER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <map>
#include <memory>
#include <set>

#include "Win32API.hpp"
#include "Ag/Core/ErrorGuard.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which can be passed between threads for execution.
class IDispatcherTask
{
public:
    //! @brief Is called on the target thread to perform an action.
    //! @return The result of the task.
    virtual intptr_t execute() =0;

    //! @brief Disposes of the task instance once it is no longer needed.
    virtual void destroy() = 0;
};

//! @brief An alias for a pointer to a function used to perform idle tasks in
//! a running dispatcher.
typedef void (*IdleProc)(uintptr_t context);

//! @brief An alias for a pointer to a function used to determine if a local
//! message processing loop should exit, perhaps for a modal dialog.
typedef bool (*ExecCondition)(uintptr_t context);

//! @brief A structure describing a task to execute when the dispatcher
//! is idle.
struct IdleTask
{
    IdleProc Procedure;
    uintptr_t Context;
};

//! @brief Internal dispatcher data shared between instances on the same
//! thread.
struct DispatcherData : std::enable_shared_from_this<DispatcherData>
{
    // Public Data
    uint32_t _threadId;
    std::map<uint32_t, IdleTask> _idleTasks;
    std::set<HWND> _dialogWindows;
    ErrorGuard _guard;
    bool _exitRequested;

    // Construction
    DispatcherData();
};

//! @brief An alias of a shared pointer to DispatcherData.
using DispatcherDataSPtr = std::shared_ptr<DispatcherData>;

//! @brief An alias of a weak pointer to DispatcherData.
using DispatcherDataWPtr = std::weak_ptr<DispatcherData>;

//! @brief A reference to a dispatcher operating on a different thread.
class DispatcherReference
{
public:
    // Construction/Destruction
    DispatcherReference(const DispatcherDataSPtr &source);

    // Operations
    bool invokeTask(IDispatcherTask *task) const;
private:
    // Internal Fields
    DispatcherDataWPtr _externalDispatcher;
};

//! @brief An object which processes raw Win32 input messages for a thread.
class Dispatcher
{
public:
    // Construction/Destruction
    Dispatcher();
    virtual ~Dispatcher();

    // Accessors
    bool isExitRequested() const;
    uint32_t getThreadId() const;
    bool isForCurrentThread() const;
    DispatcherReference getReference() const;
    void invokeTask(IDispatcherTask *task) const;

    // Operations
    int exec();
    int execConditional(ExecCondition testFn, uintptr_t context);
    void scheduleIdleTask(uint32_t id, IdleProc idleProc, uintptr_t context);
    void unscheduleIdleTask(uint32_t id);
    void addDialogWindow(HWND handle);
    void removeDialogWindow(HWND handle);

    // Overrides
protected:
    virtual intptr_t processThreadMessage(MSG &message);
    virtual intptr_t processWindowMessage(MSG &message);

    // Internal Types

    // Internal Functions
    void requestExit();

private:
    static bool exitRequested(uintptr_t context);

private:
    // Internal Fields
    DispatcherDataSPtr _current;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
