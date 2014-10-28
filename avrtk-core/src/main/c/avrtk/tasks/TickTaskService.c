/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/tasks/TickTaskService.h
 *
 * @brief Definition of the TickTaskService class methods.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/tasks/TickTaskService.h>
#include <avrtk/ticks/TickEventType.h>





/**********************************************************************//**
 *
 * @class TickTaskService avrtk/tasks/TickTaskService.h <avrtk/tasks/TickTaskService.h> @ingroup avrtk_tasks
 *
 * @brief A concrete implementation of the TaskService interface that
 * uses a Clock to schedule the execution of tasks.
 *
 **************************************************************************/





static void TickTaskService_start(TaskService  *self);

static void TickTaskService_addTask(TaskService *baseSelf,
                                    Task        *task,
                                    long         delay);

static void TickTaskService_addPeriodicTask(TaskService *baseSelf,
                                            Task        *task,
                                            long         delay,
                                            long         period);

static void TickTaskService_cancelTask(TaskService *self,
                                       Task        *task);

static void TickTaskService_tickEvent(TickTaskService *self);


static TaskServiceInterface interface = {
    .start           = TaskServiceInterface_start,
    .addTask         = TaskServiceInterface_addTask,
    .addPeriodicTask = TaskServiceInterface_addPeriodicTask,
    .cancelTask      = TaskServiceInterface_cancelTask
};





static EventListener *
TaskServiceTickListener_asEventListener(TaskServiceTickListener *self);

static void
TaskServiceTickListener_init(TaskServiceTickListener *self,
                             TickTaskService             *taskService);

static void
TaskServiceTickListener_notify(EventListener *self,
                               Event         *Event);


static EventListenerInterface taskServiceEventListenerInterface = {
    .notify = TaskServiceTickListener_notify
};





/**********************************************************************//**
 *
 * Initializes a TickTaskService object.
 *
 * @public @memberof TickTaskService
 *
 * @param self Reference to the TickTaskService object to be initialized.
 *
 * @param eventManager Reference to the EventManager instance to be
 * used internally.
 *
 * @param clock Reference to the Clock instance used to obtain the
 * system time.
 *
 * @return A reference to the object just initialized. This will be
 * the same as the self argument.
 *
 **************************************************************************/

TickTaskService *TickTaskService_init(TickTaskService *self,
                                      EventManager    *eventManager,
                                      Clock           *clock) {

    self->eventManager = eventManager;
    TaskScheduler_init(&self->scheduler, clock);
    TaskServiceTickListener_init(&self->tickListener, self);

    return self;
}






/**********************************************************************//**
 *
 * Starts the TickTaskService.
 *
 * @public @memberof TickTaskService
 *
 * Upon returning from this method, the TickTaskService will start
 * listening for tick events distributed by the EventManager.
 *
 * @param self Reference to the TickTaskService object being used.
 *
 **************************************************************************/

static void TickTaskService_start(TaskService  *self) {

    TickTaskService *self         = (TickTaskService *)baseSelf;
    EventListener   *tickListener =
        TaskServiceTickListener_asEventListener(&self->tickListener);

    EventManager_addListener(self->eventManager,
                             TickEventType_get(),
                             tickListener);
}





/**********************************************************************//**
 *
 * Adds a task to be executed after the given delay.
 *
 * @public @memberof TickTaskService
 *
 * The task object is allowed during the execution of its Task_run
 * method to invoke methods on this same TickTaskService to add or cancel
 * other tasks. The task object can even add itself to this
 * TickTaskService.
 *
 * @param self Reference to the TickTaskService object being used.
 *
 * @param task Reference to the Task instance to be executed.
 *
 * @param delay Delay, in milliseconds, after which the task is to be
 * executed.
 *
 **************************************************************************/

static void TickTaskService_addTask(TaskService *baseSelf,
                                    Task        *task,
                                    long         delay) {

    TickTaskService *self = (TickTaskService *)baseSelf;

    TaskScheduler_addTask(&self->scheduler, task, delay);
}






/***********************************************************************//**
 *
 * Adds a task to be executed periodically after a given delay. The
 * Task will be in use until the given task is cancelled.
 *
 * @public @memberof TickTaskService
 *
 * This method can be called from within a task being run by
 * TickTaskService_runPendingTasks.
 *
 **************************************************************************/

static void TickTaskService_addPeriodicTask(TaskService *baseSelf,
                                            Task        *task,
                                            long         delay,
                                            long         period) {

    TickTaskService *self = (TickTaskService)baseSelf;

    TaskScheduler_addPeriodicTask(&self->scheduler, task, delay, period);
}






/**********************************************************************//**
 *
 * The Task is guaranteed to be no longer in use by the TickTaskService by
 * the time this method returns.
 *
 * @public @memberof TickTaskService
 *
 * This method can be called from within a task being run by
 * TickTaskService_runPendingTasks.
 *
 **************************************************************************/

static void TickTaskService_cancelTask(TaskService *self,
                                       Task        *task) {

    TickTaskService *self = (TickTaskService)baseSelf;

    TaskScheduler_cancelTask(&self->scheduler, task);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void TickTaskService_tickEvent(TickTaskService *self) {

    TaskScheduler_runPendingTasks(&self->scheduler);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void
TaskServiceTickListener_init(TaskServiceTickListener *self,
                             TickTaskService              *taskService) {

    self->base.vtable = &taskServiceEventListenerInterface;
    self->taskService = taskService;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static EventListener *
TaskServiceTickListener_asEventListener(TaskServiceTickListener *self) {

    EventListener *result = (EventListener *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void TaskServiceTickListener_notify(EventListener *baseSelf,
                                           Event         *Event) {

    TaskServiceTickListener *self = (TaskServiceTickListener *)baseSelf;

    TickTaskService_tickEvent(self->taskService);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

