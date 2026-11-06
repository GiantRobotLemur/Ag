//! @file Ag/Sdl3Tools/EventProcessor.hpp
//! @brief The declaration of an object which manages the SDL input event
//! processing loop.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_EVENT_PROCESSOR_HPP__
#define __AG_SDL3_TOOLS_EVENT_PROCESSOR_HPP__

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
using TimerTick_t = decltype(SDL_GetTicks());

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which is called to perform a periodic task.
struct PeriodicTask : public std::enable_shared_from_this<PeriodicTask>
{
protected:
    // Construction/Destruction
    PeriodicTask() = default;
public:
    virtual ~PeriodicTask() = default;

    // Overrides
    virtual bool execute(double elapsedTimeInSeconds) = 0;
};

//! @brief An alias for a shared pointer to an object which can perform
//! periodic processing.
using PeriodicTaskSPtr = std::shared_ptr<PeriodicTask>;
using PeriodicCallbackFn = bool (*)(uintptr_t context, double timeDelta);

//! @brief An object which has state and can handle an SDL input event.
struct EventHandler : public std::enable_shared_from_this<EventHandler>
{
protected:
    // Construction/Destruction
    EventHandler() = default;
public:
    virtual ~EventHandler() = default;

    // Overrides
    virtual bool execute(SDL_Event *info) =0;
};

//! @brief An alias for a pointer to an object which can process an SDL
//! input message.
using EventHandlerSPtr = std::shared_ptr<EventHandler>;

//! @brief A pointer to a static function to handle an SDL event.
//! @param[in] context User context registered with the handler.
//! @param[in] info Details of the event being handled.
//! @retval true Event processing can continue.
//! @retval false Signals that the event loop should exit.
using EventHandlerFn = bool (*)(uintptr_t context, SDL_Event *info);

//! @brief An object which dispatches event handlers registered with it.
class EventHandlers
{
public:
    // Construction/Destruction
    EventHandlers();
    virtual ~EventHandlers() = default;

    // Accessors
    bool hasHandlers() const;

    // Operations
    void optimise();
    bool dispatchEvent(SDL_Event &eventInfo);
    uint32_t registerEventHandler(SDL_EventType type, const EventHandlerSPtr &handler);
    uint32_t registerEventHandler(SDL_EventType type, EventHandlerFn handlerFn, uintptr_t context = 0);
    uint32_t registerCustomEventHandler(uint32_t typeId, const EventHandlerSPtr &handler);
    uint32_t registerCustomEventHandler(uint32_t typeId, EventHandlerFn handlerFn, uintptr_t context = 0);
    void deregisterEventHandler(uint32_t id);
    void deregisterEventHandler(SDL_EventType type, const EventHandlerSPtr &handler);
    void deregisterEventHandler(SDL_EventType type, EventHandlerFn handlerFn, uintptr_t context = 0);

private:
    // Internal Types
    class EventHandlerNode
    {
    public:
        // Construction/Destruction
        EventHandlerNode();
        EventHandlerNode(uint32_t id, const EventHandlerSPtr &handler);
        EventHandlerNode(uint32_t id, EventHandlerFn handlerFn, uintptr_t context);
        ~EventHandlerNode() = default;

        // Accessors
        uint32_t getID() const;
        bool matches(const EventHandlerSPtr &handler) const;
        bool matches(EventHandlerFn handlerFn, uintptr_t context) const;

        // Operations
        bool execute(SDL_Event *info) const;
    private:
        // Internal Fields
        EventHandlerSPtr _dynamicHandler;
        EventHandlerFn _staticHandler;
        uintptr_t _staticContext;
        uint32_t _id;
    };

    using EventHandlerMap = LinearSortedMap<uint32_t, EventHandlerNode>;

    // Internal Fields
    EventHandlerMap _typedEvents;
    uint32_t _handlerSeed;
};



//! @brief An object which allows the program to manage the event loop,
//! only providing supporting functions.
class EventProcessingManager
{
public:
    // Construction/Destruction
    EventProcessingManager() = default;
    virtual ~EventProcessingManager() = default;

    // Accessors
    bool isPendingExit() const;
    EventHandlers &getEventDispatcher();
    const EventHandlers &getEventDispatcher() const;

    // Operations
    void requestExit();
    void resetExitRequest();
    bool processOutstandingEvents();
protected:
    // Internal Types

    // Internal Functions
    bool processEvent(SDL_Event &currentEvent);

private:
    // Internal Fields
    EventHandlers _handlers;
    bool _exitRequested = false;
};


//! @brief An object which manages the SDL input event processing loop.
class EventProcessor : public EventProcessingManager
{
public:
    // Construction/Destruction
    EventProcessor() = default;

    // Accessors
    bool isRunning() const;

    // Operations
    void run();

protected:
    // Overrides
    virtual void runInternal();

    // Internal Functions

private:
    // Internal Fields
    bool _isRunning = false;
};

//! @brief An event processor which waits for input events, periodically
//! performing idle processing if required.
class IdleEventProcessor : public EventProcessor
{
public:
    // Construction/Destruction
    IdleEventProcessor() = default;
    virtual ~IdleEventProcessor() = default;

    // Overrides
protected:
    virtual void runInternal() override;
};

//! @brief An event processor which performs processing in cycles synchronised
//! based on user supplied logic.
class SynchronisedEventProcessor : public EventProcessor
{
public:
    // Construction/Destruction
    SynchronisedEventProcessor() = default;
    virtual ~SynchronisedEventProcessor() = default;

protected:
    // Overrides

    //! @brief A member function called on each iteration of the cycle, after
    //! input messages have been processed, but before synchroniseCycle().
    //! @param[in] secsSinceLastIteration The count of seconds since the last
    //! call to this member function.
    //! @remarks
    //! Derived classes might implement a game loop update function which
    //! updates the scene based on the elapsed time.
    virtual void onCycleExecuted(double secsSinceLastIteration) = 0;

    //! @brief A member function called at the end of each cycle to synchronise
    //! execution in some programmer defined way.
    //! @remarks
    //! Derived classes might implement a display buffer swap in this function
    //! which blocks waiting for VSync, or some other timer-based method.
    virtual void synchroniseCycle() = 0;

    virtual void runInternal() override;
};

//! @brief An event processor which locks to a fixed processing rate.
class PeriodicEventProcessor : public EventProcessor
{
public:
    // Construction/Destruction
    PeriodicEventProcessor(SDL_DisplayID syncToDisplay = 0);
    virtual ~PeriodicEventProcessor() = default;

    // Operations
    uint32_t schedulePeriodicTask(const PeriodicTaskSPtr &task, uint32_t priority = 0);
    uint32_t schedulePeriodicTask(PeriodicCallbackFn taskFn, uintptr_t taskContext = 0, uint32_t priority = 0);
    bool removePeriodicTask(uint32_t taskID);
    bool removePeriodicTask(const PeriodicTaskSPtr &task);
    bool removePeriodicTask(PeriodicCallbackFn taskFn, uintptr_t taskContext = 0);

    // Overrides
protected:
    virtual void runInternal() override;

    // Internal Types
    class PeriodicCall
    {
    public:
        PeriodicCall();
        PeriodicCall(uint32_t id, uint32_t priority, const PeriodicTaskSPtr &task);
        PeriodicCall(uint32_t id, uint32_t priority, PeriodicCallbackFn taskFn, uintptr_t taskContext);
        ~PeriodicCall() = default;

        // Accessors
        uint32_t getID() const;
        uint32_t getPriority() const;
        bool operator==(const PeriodicCall &rhs) const;
        bool matches(const PeriodicTaskSPtr &task) const;
        bool matches(PeriodicCallbackFn taskFn, uintptr_t taskContext);

        // Operations
        bool execute(double timeElapsed) const;
    private:
        // Internal Fields
        PeriodicTaskSPtr _dynamicTask;
        PeriodicCallbackFn _staticTask;
        uintptr_t _staticContext;
        uint32_t _priority;
        uint32_t _id;
    };

    // Internal Functions
    void insertTask(const PeriodicCall &call);

    // Internal Fields
    std::vector<PeriodicCall> _periodicTasks;
    double _loopPeriod;
    uint32_t _taskIDSeed;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
