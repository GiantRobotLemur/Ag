//! @file Win32Base/Dispatcher.cpp
//! @brief The definition of an object which processes raw Win32 input messages
//! for a thread.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2023
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <atomic>

#include "Ag/Core/Exception.hpp"
#include "Ag/Win32Base/Dispatcher.hpp"
#include "Ag/Win32Base/Tools.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Win32 {

//! @brief The alias of the windows message identifier used to send tasks
//! between threads.
constexpr uint32_t WM_INVOKE = WM_APP + 256;

//! @brief The shared pointer to the dispatcher for the current thread.
static thread_local DispatcherDataSPtr _threadDispatcher;

//! @brief Attempts to post a task to another thread for execution.
//! @param[in] task The task to post and then dispose of.
//! @param[i] threadId The identifier of the thread to post to.
//! @param[out] errorCode Receives the error code logged if the message could
//! not be posted.
//! @retval true The task was successfully sent to the specified thread.
//! @retval false The task could not be posted and was disposed of. @p errorCode
//! receives a value indicating why.
bool tryInvokeTask(IDispatcherTask *task, uint32_t threadId, uint32_t &errorCode)
{
    errorCode = ERROR_SUCCESS;
    bool isPosted = false;

    if (task != nullptr)
    {
        if (::PostThreadMessageW(threadId, WM_INVOKE, 0, reinterpret_cast<intptr_t>(task)))
        {
            isPosted = true;
        }
        else
        {
            // The post failed. We need to dispose of the task without running
            // it, but we should capture the error code first.
            errorCode = ::GetLastError();

            task->destroy();
            task = nullptr;
        }
    }

    return isPosted;
}

////////////////////////////////////////////////////////////////////////////////
// DispatcherReference Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a reference to a dispatcher which can be used to marshal
//! tasks from external threads.
DispatcherReference::DispatcherReference(const DispatcherDataSPtr &source) :
    _externalDispatcher(source)
{
}

//! @brief Invokes a task on the referenced thread.
//! @param[in] task The task to execute.
//! @retval true The task was successfully dispatched to the external thread.
//! @retval false The task was not dispatched and was disposed of.
bool DispatcherReference::invokeTask(IDispatcherTask *task) const
{
    if (auto dispatcher = _externalDispatcher.lock())
    {
        uint32_t errorCode;

        if (tryInvokeTask(task, dispatcher->_threadId, errorCode))
        {
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////
// Dispatcher Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which operates the thread message queue.
Dispatcher::Dispatcher() :
    _current(_threadDispatcher)
{
    if (!_current)
    {
        _threadDispatcher = std::make_shared<DispatcherData>();
        _current = _threadDispatcher;
    }
}

//! @brief Disposes of resources owned by the object.
Dispatcher::~Dispatcher()
{
}

//! @brief Determines whether execution of the message processing loop has been
//! requested to cease.
//! @retval true An end to message processing has been requested.
//! @retval false No exit has yet been requested.
bool Dispatcher::isExitRequested() const
{
    return _current->_exitRequested;
}

//! @brief Gets the identifier of the thread the object was constructed on.
uint32_t Dispatcher::getThreadId() const { return _current->_threadId; }

//! @brief Determines if the current thread is the thread the object was
//! originally constructed on.
//! @retval true The current thread is the one which owns the object.
//! @retval false The current thread is different from the on which the object
//! was constructed on.
bool Dispatcher::isForCurrentThread() const
{
    return _current->_threadId == ::GetCurrentThreadId();
}

//! @brief Gets a reference to the current dispatcher which can be used
//! from other threads.
DispatcherReference Dispatcher::getReference() const
{
    return DispatcherReference(_current);
}

//! @brief Posts a task to the thread which owns the dispatcher for execution.
//! @param[in] task The object representing the task to execute.
//! @details The task will be posted onto the message queue of the target
//! thread. If the thread no longer exist, the task will be disposed of before
//! execution and a Win32Excpetion will be thrown.
void Dispatcher::invokeTask(IDispatcherTask *task) const
{
    if (task != nullptr)
    {
        if (::PostThreadMessageW(_current->_threadId, WM_INVOKE, 0,
                                 reinterpret_cast<intptr_t>(task)) == FALSE)
        {
            // The post failed. We need to dispose of the task without running
            // it, but we should capture the error code first.
            uint32_t postError = ::GetLastError();

            task->destroy();
            task = nullptr;

            throw Win32Exception("PostThreadMessage()", postError);
        }
    }
}

//! @brief Executes the message loop until exit is requested.
//! @returns The word parameter of the final message processed.
int Dispatcher::exec()
{
    return execConditional(exitRequested,
                           reinterpret_cast<uintptr_t>(_current.get()));
}

//! @brief Executes the message loop until a condition becomes false.
//! @param[in] testFn A function to test for the exit condition.
//! @param[in] context The user context to pass to the condition function.
//! @return The word parameter of the last message processed.
int Dispatcher::execConditional(ExecCondition testFn, uintptr_t context)
{
    if (testFn == nullptr)
        return 0;

    MSG message;
    int threadResult = 0;

    while (testFn(context))
    {
        // Process all outstanding messages.
        while (::PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE) != FALSE)
        {
            intptr_t result = 0;

            if (message.hwnd == nullptr)
            {
                // Its a thread message.
                result = processThreadMessage(message);
            }
            else
            {
                // Its a window message.
                result = processWindowMessage(message);
            }

            if (message.message == WM_QUIT)
            {
                // Harvest the thread result and ensure the thread exits.
                threadResult = static_cast<int>(message.wParam);
                _current->_exitRequested = true;
            }
        }

        if (_current->_exitRequested == false)
        {
            if (_current->_idleTasks.empty() == false)
            {
                // Iterate through idle tasks in such a way that any tasks added
                // or removed by tasks we execute don't cause an issue.
                for (const auto &taskMapping : _current->_idleTasks)
                {
                    // TODO: Change task signature to return a bool,
                    // true to leave, false to remove the task from the
                    // scheduling map.
                    const IdleTask &task = taskMapping.second;

                    _current->_guard.tryExecProcedure(task.Procedure, task.Context);
                }
            }
        }

        if (_current->_exitRequested == false)
        {
            // TODO: Implement more complex blocking when additional wait
            // handles or idle processing is supported.
            ::WaitMessage();
        }
    }

    return threadResult;
}

//! @brief Schedules a task to be run periodically when there are no input
//! message to process.
//! @param[in] id The identifier of the task unique within the current
//! dispatcher.
//! @param[in] idleProc The procedure to call during idle time.
//! @param[in] context A value to pass to idleProc when it is called.
void Dispatcher::scheduleIdleTask(uint32_t id, IdleProc idleProc, uintptr_t context)
{
    IdleTask task;
    task.Procedure = idleProc;
    task.Context = context;

    _current->_idleTasks[id] = task;
}

//! @brief Removes idle tasks which match a specified identifier.
//! @param[in] id The identifier of the idle task to remove.
void Dispatcher::unscheduleIdleTask(uint32_t id)
{
    _current->_idleTasks.erase(id);
}

//! @brief Adds to the set of windows which receive dialog keyboard message
//! processing.
//! @param[in] handle The handle of the window to register for additional
//! processing.
void Dispatcher::addDialogWindow(HWND handle)
{
    _current->_dialogWindows.insert(handle);
}

//! @brief Removes a window from the set which receive additional keyboard
//! message processing.
//! @param[in] handle THe handle of the window to remove.
void Dispatcher::removeDialogWindow(HWND handle)
{
    _current->_dialogWindows.erase(handle);
}

//! @brief Processes thread messages.
//! @param[in] message The message to process.
//! @returns The result of processing the message.
//! @details The base class implementation processes the WM_INVOKE message in
//! order to execute IDispatcherTask objects.
intptr_t Dispatcher::processThreadMessage(MSG &message)
{
    intptr_t result = 0;

    if (message.message == WM_INVOKE)
    {
        if (isValidAddress(message.lParam))
        {
            IDispatcherTask *task = reinterpret_cast<IDispatcherTask *>(message.lParam);

            // Execute the task in a guarded context.
            if (_current->_guard.tryExecMemberFunction(task,
                                                       &IDispatcherTask::execute,
                                                       result) == false)
            {
                result = 0;
            }

            // Dispose of the task object.
            task->destroy();
        }
    }

    return result;
}

//! @brief Processes a message meant for a window.
//! @param[in] message The message to process and deliver.
//! @returns The result of processing the message.
//! @details The base implementation simply calls TranslateMessage() followed
//! by DispatchMessage().
intptr_t Dispatcher::processWindowMessage(MSG &message)
{
    for (HWND keyboardWindow : _current->_dialogWindows)
    {
        if (::IsDialogMessageW(keyboardWindow, &message))
        {
            return 0;
        }
    }

    ::TranslateMessage(&message);
    return ::DispatchMessageW(&message);
}

//! @brief Requests that the thread exit after all currently outstanding messages
//! have been processed.
void Dispatcher::requestExit()
{
    _current->_exitRequested = true;
}

//! @brief A dispatcher condition function which test the exit requested flag.
//! @param[in] context A pointer to the DispatcherData object containing the flag.
//! @retval true To continue executing.
//! @retval false To exit the message loop.
bool Dispatcher::exitRequested(uintptr_t context)
{
    bool canContinue = false;

    if (auto dispatcher = reinterpret_cast<DispatcherData *>(context))
    {
        canContinue = (dispatcher->_exitRequested == false);
    }

    return canContinue;
}

//! @brief Constructs dispatcher state data for the current thread.
DispatcherData::DispatcherData() :
    _threadId(::GetCurrentThreadId()),
    _exitRequested(false)
{
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////

