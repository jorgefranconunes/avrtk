/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef TASKSERVICE_H
#define TASKSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/EventListener.h>
#include <avrtk/events/EventManager.h>
#include <avrtk/tasks/Task.h>
#include <avrtk/tasks/TaskScheduler.h>
#include <avrtk/ticks/Clock.h>





    typedef struct TaskServiceStruct TaskService;


    typedef struct TaskServiceTickListenerStruct TaskServiceTickListener;
    struct TaskServiceTickListenerStruct {
        EventListener base;
        TaskService  *taskService;
    };


    struct TaskServiceStruct {
        EventManager           *eventManager;
        TaskScheduler           scheduler;
        TaskServiceTickListener tickListener;
    };

    TaskService *TaskService_init(TaskService  *self,
                                  EventManager *eventManager,
                                  Clock        *clock);

    void TaskService_start(TaskService *self);

    void TaskService_addTask(TaskService *self,
                             Task        *task,
                             long         delay);

    void TaskService_addPeriodicTask(TaskService *self,
                                     Task        *task,
                                     long         delay,
                                     long         period);

    void TaskService_cancelTask(TaskService *self,
                                Task        *task);





#ifdef __cplusplus
}
#endif

#endif
