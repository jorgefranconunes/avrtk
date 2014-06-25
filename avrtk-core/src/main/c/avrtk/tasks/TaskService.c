/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

/**
 *
 * @file avrtk/tasks/TaskService.h
 *
 * @brief Definition of the TaskService class methods.
 *
 */

/**
 *
 * @class TaskService avrtk/tasks/TaskService.h <avrtk/tasks/TaskService.h>
 *
 * @brief Used for executing tasks at a given time or periodically.
 *
 */

#include <stddef.h>

#include <avrtk/tasks/TaskService.h>
#include <avrtk/ticks/TickEventType.h>





static EventListener *
TaskServiceTickListener_asEventListener(TaskServiceTickListener *self);

static void
TaskServiceTickListener_init(TaskServiceTickListener *self,
                             TaskService             *taskService);

static void
TaskServiceTickListener_notify(EventListener *self,
                               Event         *Event);

static EventListenerInterface taskServiceEventListenerInterface = {
    .notify = TaskServiceTickListener_notify
};





static void TaskService_tickEvent(TaskService *self);





/**********************************************************************//**
 *
 * Initializes a TaskService object.
 *
 * @public @memberof TaskService
 *
 * @param self Reference to the TaskService object to be initialized.
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

TaskService *TaskService_init(TaskService  *self,
                              EventManager *eventManager,
                              Clock        *clock) {

    self->eventManager = eventManager;
    TaskScheduler_init(&self->scheduler, clock);
    TaskServiceTickListener_init(&self->tickListener, self);

    return self;
}






/**********************************************************************//**
 *
 * Starts the TaskService.
 *
 * @public @memberof TaskService
 *
 * Upon returning from this method, the TaskService will start
 * listening for tick events distributed by the EventManager.
 *
 * @param self Reference to the TaskService object being used.
 *
 **************************************************************************/

void TaskService_start(TaskService  *self) {

    EventListener *tickListener =
        TaskServiceTickListener_asEventListener(&self->tickListener);

    EventManager_addListener(self->eventManager,
                             TickEventType_get(),
                             tickListener);
}





/**********************************************************************//**
 *
 * Adds a task to be executed after the given delay.
 *
 * @public @memberof TaskService
 *
 * The task object is allowed during the execution of its Task_run
 * method to invoke methods on this same TaskService to add or cancel
 * other tasks. The task object can even add itself to this
 * TaskService.
 *
 * @param self Reference to the TaskService object being used.
 *
 * @param task Reference to the Task instance to be executed.
 *
 * @param delay Delay, in milliseconds, after which the task is to be
 * executed.
 *
 **************************************************************************/

void TaskService_addTask(TaskService *self,
                         Task        *task,
                         long         delay) {

    TaskScheduler_addTask(&self->scheduler, task, delay);
}






/***********************************************************************//**
 *
 * Adds a task to be executed periodically after a given delay. The
 * Task will be in use until the given task is cancelled.
 *
 * @public @memberof TaskService
 *
 * This method can be called from within a task being run by
 * TaskService_runPendingTasks.
 *
 **************************************************************************/

void TaskService_addPeriodicTask(TaskService *self,
                                 Task        *task,
                                 long         delay,
                                 long         period) {

    TaskScheduler_addPeriodicTask(&self->scheduler, task, delay, period);
}






/**********************************************************************//**
 *
 * The Task is guaranteed to be no longer in use by the TaskService by
 * the time this method returns.
 *
 * @public @memberof TaskService
 *
 * This method can be called from within a task being run by
 * TaskService_runPendingTasks.
 *
 **************************************************************************/

void TaskService_cancelTask(TaskService *self,
                            Task        *task) {

    TaskScheduler_cancelTask(&self->scheduler, task);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void TaskService_tickEvent(TaskService *self) {

    TaskScheduler_runPendingTasks(&self->scheduler);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void
TaskServiceTickListener_init(TaskServiceTickListener *self,
                             TaskService              *taskService) {

    self->base.vtable = &taskServiceEventListenerInterface;
    self->taskService = taskService;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventListener *
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

    TaskService_tickEvent(self->taskService);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

