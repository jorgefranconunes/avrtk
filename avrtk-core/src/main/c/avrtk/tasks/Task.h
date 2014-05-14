/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef TASK_H
#define TASK_H

#ifdef __cplusplus
extern "C" {
#endif





    typedef enum TaskStatus {
        ACTIVE,
        CANCELED,
        DONE,
        RESCHEDULE
    } TaskStatus;


    typedef struct TaskStruct Task;

    typedef struct TaskInterfaceStruct TaskInterface;
    struct TaskInterfaceStruct {
        void (*run)(Task *);
    };

    struct TaskStruct {
        TaskInterface *vtable;
        long           when;
        long           period;
        TaskStatus     status;
        Task          *next;
    };

    void Task_run(Task *self);





#ifdef __cplusplus
}
#endif

#endif

