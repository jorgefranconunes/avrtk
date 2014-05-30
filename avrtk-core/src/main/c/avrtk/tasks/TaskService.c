/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

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





/**************************************************************************
 *
 * 
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






/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void TaskService_start(TaskService  *self) {

    EventListener *tickListener =
        TaskServiceTickListener_asEventListener(&self->tickListener);

    EventManager_addListener(self->eventManager,
                             TickEventType_get(),
                             tickListener);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void TaskService_addTask(TaskService *self,
                         Task        *task,
                         long         delay) {

    TaskScheduler_addTask(&self->scheduler, task, delay);
}






/**************************************************************************
 *
 * The Task will be in use until the given task is cancelled.
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






/**************************************************************************
 *
 * The Task is guaranteed to be no longer in use by the TaskService by
 * the time this method returns.
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

