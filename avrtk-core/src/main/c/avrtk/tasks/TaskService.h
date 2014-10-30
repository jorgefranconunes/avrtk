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

#include <avrtk/tasks/Task.h>





    typedef struct TaskServiceStruct TaskService;


    typedef struct TaskServiceInterfaceStruct TaskServiceInterface;
    struct TaskServiceInterfaceStruct {
        void (*start)(TaskService *self);
        void (*addTask)(TaskService *self,
                        Task        *task,
                        long         delay);
        void (*addPeriodicTask)(TaskService *self,
                                Task        *task,
                                long         delay,
                                long         period);
        void (*cancelTask)(TaskService *self,
                           Task        *task);
    };


    struct TaskServiceStruct {
        TaskServiceInterface *vtable;
    };

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
