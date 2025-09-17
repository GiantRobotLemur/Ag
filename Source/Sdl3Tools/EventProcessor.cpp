//! @file Sdl3Tools/EventProcessor.cpp
//! @brief The definition of an object which manages the SDL input event
//! processing loop.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Sdl3Tools/EventProcessor.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// EventHandlers Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to dispatch handlers for events.
EventHandlers::EventHandlers() :
    _handlerSeed(1)
{
}

//! @brief Determines if any handlers have been registered.
//! @retval true At least one handler is registered.
//! @retval false No handlers are registered.
bool EventHandlers::hasHandlers() const
{
    return _typedEvents.isEmpty() == false;
}

//! @brief Ensures that the event handlers are optimised for searching.
void EventHandlers::optimise()
{
    _typedEvents.reindex();
}

//! @brief Calls all handlers registered against an event.
//! @param[in,out] eventInfo The handler to process.
//! @retval true If no handlers requested an exit for the event loop.
//! @retval false At least one handler requested the event loop exit.
bool EventHandlers::dispatchEvent(SDL_Event &eventInfo)
{
    auto handlerRange = _typedEvents.findRange(eventInfo.type);
    bool result = true;

    for (auto &node : handlerRange)
    {
        result &= node.second.execute(&eventInfo);
    }

    return result;
}

//! @brief Registers an object to be called when an event is fired.
//! @param[in] type The type of event to handle.
//! @param[in] handler The object to handle the event.
//! @return The unique ID of the registered handler.
uint32_t EventHandlers::registerEventHandler(SDL_EventType type,
                                             const EventHandlerSPtr &handler)
{
    EventHandlerNode node(_handlerSeed++, handler);
    uint32_t rawType = type;

    _typedEvents.push_back(rawType, node);

    return node.getID();
}

//! @brief Registers an object to be called when an event is fired.
//! @param[in] type The type of event to handle.
//! @param[in] handlerFn A pointer to a function to handle the event.
//! @param[in] context A user specified value to pass to the function when the
//! event is being handled.
//! @return The unique ID of the registered handler.
uint32_t EventHandlers::registerEventHandler(SDL_EventType type,
                                             EventHandlerFn handlerFn,
                                             uintptr_t context /*= 0*/)
{
    EventHandlerNode node(_handlerSeed++, handlerFn, context);
    uint32_t rawType = type;

    _typedEvents.push_back(rawType, node);

    return node.getID();
}

//! @brief De-registers a unique event handler.
//! @param[in] id The unique ID of the handler returned when it was registered.
void EventHandlers::deregisterEventHandler(uint32_t id)
{
    struct NodeMatcher
    {
        uint32_t _id;
        NodeMatcher(uint32_t id) : _id(id) {}
        bool operator()(const EventHandlerMap::MappingCollection::value_type &rhs) const
        {
            return rhs.second.getID() == _id;
        }
    };

    // Perform a linear search through all mappings, sorted and otherwise.
    auto pos = std::find_if(_typedEvents.begin(), _typedEvents.mappingsEnd(), NodeMatcher(id));

    if (pos != _typedEvents.mappingsEnd())
    {
        _typedEvents.erase(pos);
    }
}

//! @brief De-registers any matching event handler.
//! @param[in] type The type of event then handler was registered against.
//! @param[in] handler The object which handled the event.
void EventHandlers::deregisterEventHandler(SDL_EventType type,
                                           const EventHandlerSPtr &handler)
{
    uint32_t rawType = type;

    // Ensure the events are properly indexed.
    _typedEvents.reindex();

    auto range = _typedEvents.findRange(rawType);

    if (range.isEmpty())
        return;

    auto current = range.Begin;
    size_t count = range.getCount();

    for (size_t index = 0; index < count; ++index)
    {
        if (current->second.matches(handler))
        {
            current = _typedEvents.erase(current);
        }
        else
        {
            ++current;
        }
    }
}

//! @brief De-registers any matching event handler.
//! @param[in] type The type of event then handler was registered against.
//! @param[in] handlerFn A pointer to a function registered to handle the event.
//! @param[in] context The user context specified value to registered with
//! the handler.
void EventHandlers::deregisterEventHandler(SDL_EventType type,
                                           EventHandlerFn handlerFn,
                                           uintptr_t context /*= 0*/)
{
    uint32_t rawType = type;

    // Ensure the events are properly indexed.
    _typedEvents.reindex();

    auto range = _typedEvents.findRange(rawType);

    if (range.isEmpty())
        return;

    auto current = range.Begin;
    size_t count = range.getCount();

    for (size_t index = 0; index < count; ++index)
    {
        if (current->second.matches(handlerFn, context))
        {
            current = _typedEvents.erase(current);
        }
        else
        {
            ++current;
        }
    }
}

//! @brief Constructs an empty handler node.
EventHandlers::EventHandlerNode::EventHandlerNode() :
    _staticContext(0),
    _id(0)
{
}

//! @brief Constructs a dynamic handler node.
//! @param[in] id The unique identifier of the handler.
//! @param[in] handler The object which will handle the event.
EventHandlers::EventHandlerNode::EventHandlerNode(uint32_t id, const EventHandlerSPtr &handler) :
    _dynamicHandler(handler),
    _staticContext(0),
    _id(id)
{
}

//! @brief Constructs a static handler node.
//! @param[in] id The unique identifier of the handler.
//! @param[in] handlerFn A pointer to a function to handle the event.
//! @param[in] context A user specified value to pass to the function when the
//! event is being handled.
EventHandlers::EventHandlerNode::EventHandlerNode(uint32_t id,
                                                  EventHandlerFn handlerFn,
                                                  uintptr_t context) :
    _staticHandler(handlerFn),
    _staticContext(context),
    _id(id)
{

}

//! @brief Gets the unique identifier of the handler.
uint32_t EventHandlers::EventHandlerNode::getID() const
{
    return _id;
}

//! @brief Determines if the handler calls the specified object.
//! @param[in] handler The dynamic handler to match.
//! @retval true If the node has a matching handler.
//! @retval false If the handler doesn't match or has a static handler.
bool EventHandlers::EventHandlerNode::matches(const EventHandlerSPtr &handler) const
{
    return _dynamicHandler == handler;
}

//! @brief Determines if the handler calls the specified callback.
//! @param[in] handlerFn The static handler function to match.
//! @param[in] context The static context value to match.
//! @retval true If the node has a matching handler.
//! @retval false If the handler doesn't match or has a dynamic handler.
bool EventHandlers::EventHandlerNode::matches(EventHandlerFn handlerFn, uintptr_t context) const
{
    return (_staticHandler == handlerFn) && (_staticContext == context);
}

//! @brief Executes the handler the node describes.
//! @param[in] info A pointer to the event being handled.
//! @return The result of handling the event.
bool EventHandlers::EventHandlerNode::execute(SDL_Event *info) const
{
    if (_dynamicHandler)
        return _dynamicHandler->execute(info);
    else if (_staticHandler != nullptr)
        return _staticHandler(_staticContext, info);
    else
        return true;
}

////////////////////////////////////////////////////////////////////////////////
// EventProcessor Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Construct an object which processes input event.
EventProcessor::EventProcessor() :
    _isRunning(false),
    _exitRequested(false)
{
}

//! @brief Determines if the run() member function is currently active.
bool EventProcessor::isRunning() const
{
    return _isRunning;
}

//! @brief Determines whether the a pending request has been made to exit the
//! current event processing loop.
//! @retval true A pending request exists.
//! @retval false The processing loop can continue.
bool EventProcessor::isPendingExit() const
{
    return _exitRequested;
}

//! @brief Gets the object which maps events to handlers.
EventHandlers &EventProcessor::getEventDispatcher()
{
    return _handlers;
}

//! @brief Gets the object which maps events to handlers.
const EventHandlers &EventProcessor::getEventDispatcher() const
{
    return _handlers;
}

//! @brief Requests that the current message processing loop exit.
void EventProcessor::requestExit()
{
    _exitRequested = true;
}

//! @brief Runs the message processing loop until exit is requested.
//! @detail If the run() method is already active, the call will return
//! immediately.
void EventProcessor::run()
{
    if (_isRunning)
        return;

    // Ensure event handlers are properly indexed.
    _handlers.optimise();

    _exitRequested = false;

    // Mark the loop as running until runInternal() returns.
    ValueScope<bool> runningScope(_isRunning, true);

    runInternal();
}

//! @brief Processes a single event.
//! @param[in] currentEvent The event to process.
//! @retval true Event processing should continue.
//! @retval false The event processing loop should exit.
bool EventProcessor::processEvent(SDL_Event &currentEvent)
{
    return _handlers.dispatchEvent(currentEvent);
}

////////////////////////////////////////////////////////////////////////////////
// IdleEventProcessor Member Definitions
////////////////////////////////////////////////////////////////////////////////
// Inherited from EventProcessor.
void IdleEventProcessor::runInternal()
{
    // TODO: Implement non-busy waiting and idle task scheduling.
}

////////////////////////////////////////////////////////////////////////////////
// BusyEventProcessor Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an event processor object which is synchronised to a fixed
//! cycle time period.
//! @param[in] syncToDisplay The optional identifier of the display to sync the
//! to the refresh rate of.
PeriodicEventProcessor::PeriodicEventProcessor(SDL_DisplayID syncToDisplay /*= 0*/) :
    _loopPeriod(1.0),
    _taskIDSeed(1)
{
    // Default the refresh rate to that of the primary display.
    if (syncToDisplay == 0)
        return;

    auto displayMode = SDL_GetCurrentDisplayMode(syncToDisplay);

    if (displayMode != nullptr)
    {
        _loopPeriod = 1.0 / displayMode->refresh_rate;
    }

    _periodicTasks.reserve(16);
}

//! @brief Schedules a dynamic task to run once per cycle.
//! @param[in] task The task to execute.
//! @param[in] priority The priority of the task, the lower the value, the
//! sooner the task will run.
//! @return The unique identifier of the scheduled task.
uint32_t PeriodicEventProcessor::schedulePeriodicTask(const PeriodicTaskSPtr &task,
                                                  uint32_t priority /*= 0*/)
{
    PeriodicCall call(_taskIDSeed++, priority, task);

    insertTask(call);

    return call.getID();
}

//! @brief Schedules a static callback task to run once per cycle.
//! @param[in] taskFn The function to call once per cycle.
//! @param[in] taskContext The context value to pass to the task.
//! @param[in] priority The priority of the task, the lower the value, the
//! sooner the task will run.
//! @return The unique identifier of the scheduled task.
uint32_t PeriodicEventProcessor::schedulePeriodicTask(PeriodicCallbackFn taskFn,
                                                      uintptr_t taskContext /*= 0*/,
                                                      uint32_t priority /*= 0*/)
{
    PeriodicCall call(_taskIDSeed++, priority, taskFn, taskContext);

    insertTask(call);

    return call.getID();
}

//! @brief Removes all scheduled periodic tasks with a specific ID.
//! @param[in] taskID The identifier of the task to remove.
//! @retval true At least one task was removed.
//! @retval false No matching tasks were found.
bool PeriodicEventProcessor::removePeriodicTask(uint32_t taskID)
{
    bool isErased = false;

    for (auto pos = _periodicTasks.begin(); pos != _periodicTasks.end(); )
    {
        if (pos->getID() == taskID)
        {
            pos = _periodicTasks.erase(pos);
            isErased = true;
        }
        else
        {
            ++pos;
        }
    }

    return isErased;
}

//! @brief Removes all scheduled periodic tasks with matching a specified pointer.
//! @param[in] task The dynamic task to remove.
//! @retval true At least one task was removed.
//! @retval false No matching tasks were found.
bool PeriodicEventProcessor::removePeriodicTask(const PeriodicTaskSPtr &task)
{
    bool isErased = false;

    for (auto pos = _periodicTasks.begin(); pos != _periodicTasks.end(); )
    {
        if (pos->matches(task))
        {
            pos = _periodicTasks.erase(pos);
            isErased = true;
        }
        else
        {
            ++pos;
        }
    }

    return isErased;
}

//! @brief Removes all scheduled periodic tasks with matching a specified pointer and context.
//! @param[in] taskFn The static task callback to remove.
//! @param[in] taskContext The context associated with the static task to remove.
//! @retval true At least one task was removed.
//! @retval false No matching tasks were found.
bool PeriodicEventProcessor::removePeriodicTask(PeriodicCallbackFn taskFn,
                                                uintptr_t taskContext /*= 0*/)
{
    bool isErased = false;

    for (auto pos = _periodicTasks.begin(); pos != _periodicTasks.end(); )
    {
        if (pos->matches(taskFn, taskContext))
        {
            pos = _periodicTasks.erase(pos);
            isErased = true;
        }
        else
        {
            ++pos;
        }
    }

    return isErased;
}

// Inherited from EventProcessor.
void PeriodicEventProcessor::runInternal()
{
    using PerfCounter_t = decltype(SDL_GetPerformanceCounter());

    constexpr TimerTick_t MsToNs = static_cast<TimerTick_t>(1000000);
    constexpr int MaxEvents = 16;
    SDL_Event eventInfo[MaxEvents];

    double perfFrequency = static_cast<double>(SDL_GetPerformanceFrequency());

    // Initially query for events.
    SDL_PumpEvents();
    PerfCounter_t lastLoopStart = SDL_GetPerformanceCounter();

    while (!isPendingExit())
    {
        // Process outstanding events.
        TimerTick_t startTime = SDL_GetTicks();
        int eventCount = 0;

        do
        {
            // Fill the array with events to process.
            eventCount = SDL_PeepEvents(eventInfo, MaxEvents, SDL_GETEVENT,
                                        SDL_EVENT_FIRST, SDL_EVENT_LAST);

            // Check for a polling failure.
            if (eventCount < 0)
                throw ApiException("SDL_PeepEvents");

            for (int i = 0; i < eventCount; ++i)
            {
                auto &currentEvent = eventInfo[i];

                if (!processEvent(currentEvent) ||
                    (currentEvent.type == SDL_EVENT_QUIT))
                {
                    requestExit();
                    break;
                }
            }

            // If we didn't fill the array, don't request more events.
            if (eventCount < MaxEvents)
                eventCount = 0;

        } while (eventCount > 0);

        // Perform periodic processing.
        auto currentTime = SDL_GetPerformanceCounter();
        auto ticksSinceLastLoop = currentTime - lastLoopStart;
        double secondsSinceLastLoop = ticksSinceLastLoop / perfFrequency;
        lastLoopStart = currentTime;

        for (auto &task : _periodicTasks)
        {
            task.execute(secondsSinceLastLoop);
        }

        // Asynchronously poll for more input events.
        SDL_PumpEvents();

        // Synchronise the loop.
        auto loopDuration = SDL_GetTicks() - startTime;
        auto preferredDuration = static_cast<TimerTick_t>(std::rint(_loopPeriod * 1000.0));

        if (loopDuration < preferredDuration)
        {
            SDL_DelayPrecise((preferredDuration - loopDuration) * MsToNs);
        }
    }
}

//! @brief Constructs an empty object describing a periodic task.
PeriodicEventProcessor::PeriodicCall::PeriodicCall() :
    _staticTask(nullptr),
    _staticContext(0),
    _priority(0),
    _id(0)
{
}

//! @brief Constructs an object describing a periodic dynamic task.
//! @param[in] id The unique identifier of the task.
//! @param[in] priority The value used to determine when the task is scheduled.
//! @param[in] task The dynamic task to call.
PeriodicEventProcessor::PeriodicCall::PeriodicCall(uint32_t id, uint32_t priority,
                                                   const PeriodicTaskSPtr &task) :
    _dynamicTask(task),
    _staticTask(nullptr),
    _staticContext(0),
    _priority(priority),
    _id(id)
{
}

//! @brief Constructs an object describing a periodic dynamic task.
//! @param[in] id The unique identifier of the task.
//! @param[in] priority The value used to determine when the task is scheduled.
//! @param[in] taskFn A pointer to a static function to call to execute the task.
//! @param[in] taskContext A value to pass to the task function.
PeriodicEventProcessor::PeriodicCall::PeriodicCall(uint32_t id, uint32_t priority,
                                                   PeriodicCallbackFn taskFn,
                                                   uintptr_t taskContext) :
    _staticTask(taskFn),
    _staticContext(taskContext),
    _priority(priority),
    _id(id)
{
}

//! @brief Gets the unique identifier of the task.
uint32_t PeriodicEventProcessor::PeriodicCall::getID() const
{
    return _id;
}

//! @brief Gets the priority of the task.
uint32_t PeriodicEventProcessor::PeriodicCall::getPriority() const
{
    return _priority;
}

bool PeriodicEventProcessor::PeriodicCall::operator==(const PeriodicCall &rhs) const
{
    if (rhs._dynamicTask)
        return _dynamicTask == rhs._dynamicTask;
    else
        return (_staticTask == rhs._staticTask) && (_staticContext == rhs._staticContext);
}

//! @brief Determines if the object wraps the specified dynamic task.
//! @param[in] task The task to match.
//! @retval true The object wraps the specified task.
//! @retval false The object wraps a different task.
bool PeriodicEventProcessor::PeriodicCall::matches(const PeriodicTaskSPtr &task) const
{
    return _dynamicTask == task;
}

//! @brief Determines if the object wraps the specified dynamic task.
//! @param[in] taskFn The task callback to match.
//! @param[in] taskContext The context value to match.
//! @retval true The object wraps the specified task.
//! @retval false The object wraps a different task.
bool PeriodicEventProcessor::PeriodicCall::matches(PeriodicCallbackFn taskFn,
                                                   uintptr_t taskContext)
{
    return (_staticTask == taskFn) && (taskContext == _staticContext);
}

//! @brief Executes the wrapped task.
//! @param[in] timeElapsed The elapsed time in seconds since the last cycle.
//! @retval true If the event loop should continue.
//! @retval false The current event loop should exit.
bool PeriodicEventProcessor::PeriodicCall::execute(double timeElapsed) const
{
    if (_dynamicTask)
        return _dynamicTask->execute(timeElapsed);
    else if (_staticTask != nullptr)
        return _staticTask(_staticContext, timeElapsed);
    else
        return true;
}

//! @brief Inserts a new task in the prioritised collection.
//! @param[in] call The call to insert.
void PeriodicEventProcessor::insertTask(const PeriodicCall &call)
{
    for (auto pos = _periodicTasks.begin(); pos != _periodicTasks.end(); ++pos)
    {
        if (pos->getPriority() >= call.getPriority())
        {
            _periodicTasks.insert(pos, call);
            return;
        }
    }

    _periodicTasks.push_back(call);
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////

