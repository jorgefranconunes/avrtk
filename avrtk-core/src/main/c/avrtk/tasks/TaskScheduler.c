/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/tasks/TaskScheduler.h
 *
 * @brief Definition of the TaskScheduler class methods.
 *
 **************************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include <avrtk/tasks/TaskScheduler.h>





/**********************************************************************//**
 *
 * @class TaskScheduler avrtk/tasks/TaskScheduler.h <avrtk/tasks/TaskScheduler.h>
 * @ingroup avrtk_tasks
 *
 * @brief Used for running tasks.
 *
 * Tasks are run synchronously upon an explicit request. All tasks
 * that are past their execution time will then be executed.
 *
 **************************************************************************/





static void TaskScheduler_addInitializedTask(TaskScheduler *self,
                                             Task          *task);





/**********************************************************************//**
 *
 * Initializes a TaskScheduler object.
 *
 * @public @memberof TaskScheduler
 * 
 * @param self Reference to the TaskScheduler object to be initialized.
 *
 * @param clock Used for obtaining the system current time when
 * checking which tasks are to be run.
 *
 **************************************************************************/

TaskScheduler *TaskScheduler_init(TaskScheduler *self,
                                  Clock         *clock) {

    self->clock        = clock;
    self->taskListHead = NULL;

    return self;
}





/**********************************************************************//**
 *
 * Retrieves the number of tasks currently under control of the
 * TaskScheduler.
 *
 * @public @memberof TaskScheduler
 *
 * @param self
 *
 * @return The number of tasks that are yet to be run.
 *
 **************************************************************************/

int TaskScheduler_getTaskCount(TaskScheduler *self) {

    int count = 0;
    
    for ( Task *task=self->taskListHead; NULL!=task; task=task->next ) {
        ++count;
    }

    return count;
}





/**********************************************************************//**
 *
 * Adds a task to be executed one single time at a later time.
 * 
 * The Task will be in use until the Task is actually run by a call to
 * the TaskScheduler_runPendingTasks method.
 *
 * This method can be called from within a task being run by
 * TaskScheduler_runPendingTasks. It is also allowed to call this
 * method for the same task that is being run, as long as that task
 * had been previously added through this method.
 *
 * @public @memberof TaskScheduler
 *
 * @param self
 *
 * @param task The Task to be run at a later time.
 *
 * @param delay The delay in milliseconds, counted from the current
 * clock time, after which the task is to be executed.
 *
 **************************************************************************/

void TaskScheduler_addTask(TaskScheduler *self,
                           Task          *task,
                           long           delay) {

    TaskScheduler_addPeriodicTask(self, task, delay, 0);
}





/**********************************************************************//**
 *
 * Adds a task to be executed periodically.
 *
 * The Task will be in use until the given task is cancelled.
 *
 * This method can be called from within a task being run by
 * TaskScheduler_runPendingTasks. But only using a different Task
 * object.
 *
 * @public @memberof TaskScheduler
 *
 * @param self
 *
 * @param task The Task to be executed periodically at a later time.
 *
 * @param delay The delay in milliseconds, counted from the current
 * clock time, after which the task is to start executing
 * periodically.
 *
 * @param period The interval, in milliseconds, between consecutive
 * executions of the given task.
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





/**********************************************************************//**
 *
 * Prevents a task from being executed. If the task was a one shot
 * task then it will not be executed at all. If the task as a periodic
 * task then it will not be executed any more from now on.
 * 
 * The Task is guaranteed to be no longer in use by the TaskScheduler
 * by the time this method returns.
 *
 * This method can be called from within a task being run by
 * TaskScheduler_runPendingTasks. This means a periodic task can
 * cancel itself during its execution.
 *
 * @public @memberof TaskScheduler
 *
 * @param self
 *
 * @param task The Task to be canceled.
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





/**********************************************************************//**
 *
 * Runs all tasks that are ready to be executed.
 *
 * A task is ready to be executed if the time for its execution is in
 * the past relative to the current system time reported by the Clock
 * object.
 *
 * It is undefined behaviour call this method from within a Task being
 * executed by this TaskScheduler. Just don't do it, otherwise bad
 * things will happen to you.
 *
 * @public @memberof TaskScheduler
 *
 * @param self
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

