/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include <avrtk/tasks/TaskScheduler.h>





static void TaskScheduler_addInitializedTask(TaskScheduler *self,
                                             Task          *task);





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TaskScheduler *TaskScheduler_init(TaskScheduler *self,
                                  Clock         *clock) {

    self->clock        = clock;
    self->taskListHead = NULL;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int TaskScheduler_getPendingCount(TaskScheduler *self) {

    int count = 0;
    
    for ( Task *task=self->taskListHead; NULL!=task; task=task->next ) {
        ++count;
    }

    return count;
}





/**************************************************************************
 *
 * The Task will be in use until the Task is run by a call to the
 * TaskScheduler_runPendingTasks method.
 *
 * This method can be called from within a task being run by
 * TaskScheduler_runPendingTasks.
 *
 **************************************************************************/

void TaskScheduler_addTask(TaskScheduler *self,
                           Task          *task,
                           long           delay) {

    TaskScheduler_addPeriodicTask(self, task, delay, 0);
}





/**************************************************************************
 *
 * The Task will be in use until the given task is cancelled.
 *
 * This method can be called from within a task being run by
 * TaskScheduler_runPendingTasks.
 *
 **************************************************************************/

void TaskScheduler_addPeriodicTask(TaskScheduler *self,
                                   Task          *task,
                                   long           delay,
                                   long           period) {

    long now  = Clock_currentTimeMillis(self->clock);
    long when = now+delay;

    task->when   = when;
    task->period = period;
    task->status = ACTIVE;
    task->next   = NULL;

    TaskScheduler_addInitializedTask(self, task);
}





/**************************************************************************
 *
 * Adds an already initialized task to the pending task list.
 *
 **************************************************************************/

static void TaskScheduler_addInitializedTask(TaskScheduler *self,
                                             Task          *task) {

    long when = task->when;

    /* Insert the task at the right position in the list, keeping the
       list ordered by increasing time. */

    Task **ptask = &self->taskListHead;

    while ( NULL!=(*ptask) && (*ptask)->when<when ) {
        ptask = &(*ptask)->next;
    }
    task->next = *ptask;
    *ptask = task;
}





/**************************************************************************
 *
 * The Task is guaranteed to be no longer in use by the TaskScheduler
 * by the time this method returns.
 *
 * This method can be called from within a task being run by
 * TaskScheduler_runPendingTasks.
 *
 **************************************************************************/

void TaskScheduler_cancelTask(TaskScheduler *self,
                              Task          *task) {

    task->status = CANCELED;

    Task **ptask = &self->taskListHead;

    while ( NULL!=(*ptask) && (*ptask)!=task ) {
        ptask = &(*ptask)->next;
    }

    if ( NULL != (*ptask) ) {
        *ptask = task->next;
        task->next = NULL;
    } else {
        /* The given task is not in our list... Ignore it or boom?... */
    }
}





/**************************************************************************
 *
 * Do not call this method from within a Task. Otherwise bad things
 * will happen to you.
 *
 **************************************************************************/

void TaskScheduler_runPendingTasks(TaskScheduler *self) {

    long   now        = Clock_currentTimeMillis(self->clock);
    bool   isChecking = true;
    Task **head       = &self->taskListHead;

    while ( NULL!=(*head) && isChecking ) {
        Task *task = *head;

        if ( now < task->when ) {
            /* This task is not yet ripe. Because we keep the pending
               task list orderered, that means no more tasks are yet
               ripe and so we bail out. */
            isChecking = false;
        } else {
            /* Remove the task from the pending task list. */
            *head = (*head)->next;

            Task_run(task);

            if ( task->period > 0 ) {
                /* The task is periodic. We will re-add it to the
                   pending list. Note that it may get re-added at the
                   head of the list, and that means we will run it
                   again, if the time is right, at the next
                   iteration. */
                task->when += task->period;
                TaskScheduler_addInitializedTask(self, task);
            }
        }

    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

