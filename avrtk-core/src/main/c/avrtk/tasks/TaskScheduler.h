/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef TASKSCHEDULER_H
#define TASKSCHEDULER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/tasks/Task.h>
#include <avrtk/ticks/Clock.h>




    typedef struct TaskSchedulerStruct TaskScheduler;
    struct TaskSchedulerStruct {
        Clock *clock;
        Task  *taskListHead;
    };

    TaskScheduler *TaskScheduler_init(TaskScheduler *self,
                                      Clock         *clock);

    int TaskScheduler_getPendingCount(TaskScheduler *self);

    void TaskScheduler_addTask(TaskScheduler *self,
                               Task          *task,
                               long           delay);

    void TaskScheduler_addPeriodicTask(TaskScheduler *self,
                                       Task          *task,
                                       long           delay,
                                       long           period);

    void TaskScheduler_cancelTask(TaskScheduler *self,
                                  Task          *task);

    void TaskScheduler_runPendingTasks(TaskScheduler *self);




#ifdef __cplusplus
}
#endif

#endif
