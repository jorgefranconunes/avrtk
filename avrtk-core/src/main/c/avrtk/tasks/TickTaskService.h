/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef TICKTASKSERVICE_H
#define TICKTASKSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/EventListener.h>
#include <avrtk/events/EventManager.h>
#include <avrtk/tasks/Task.h>
#include <avrtk/tasks/TaskScheduler.h>
#include <avrtk/tasks/TaskService.h>
#include <avrtk/ticks/Clock.h>





    typedef struct TickTaskServiceStruct TickTaskService;


    typedef struct TaskServiceTickListenerStruct TaskServiceTickListener;
    struct TaskServiceTickListenerStruct {
        EventListener     base;
        TickTaskService  *taskService;
    };


    struct TickTaskServiceStruct {
        TaskService             base;
        EventManager           *eventManager;
        TaskScheduler           scheduler;
        TaskServiceTickListener tickListener;
    };

    TickTaskService *TickTaskService_init(TickTaskService *self,
                                          EventManager    *eventManager,
                                          Clock           *clock);

    TaskService *TickTaskService_asTaskService(TickTaskService *self);





#ifdef __cplusplus
}
#endif

#endif
