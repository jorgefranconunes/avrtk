/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/tasks/TaskService.h
 *
 * @brief Definition of the TaskService class methods.
 *
 **************************************************************************/

#include <avrtk/tasks/TaskService.h>





/**********************************************************************//**
 *
 * @interface TaskService avrtk/tasks/TaskService.h <avrtk/tasks/TaskService.h>
 * @ingroup avrtk_tasks
 *
 * @brief Used for executing tasks at a given future time. A task can
 * be scheduled to run only once or to run periodically.
 *
 **************************************************************************/





/**********************************************************************//**
 *
 * Starts the TaskService.
 *
 * @public @memberof TaskService
 * @pure
 *
 * Upon returning from this method, the TaskService will start
 * scheduling the tasks added to it.
 *
 * @param self Reference to the TaskService object being used.
 *
 **************************************************************************/

void TaskService_start(TaskService  *self) {

    self->vtable->start(self);
}





/**********************************************************************//**
 *
 * Adds a task to be executed after the given delay.
 *
 * @public @memberof TaskService
 * @pure
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

    self->vtable->addTask(self, task, delay);
}






/***********************************************************************//**
 *
 * Adds a task to be executed periodically after a given delay. The
 * Task will be in use until the given task is cancelled.
 *
 * @public @memberof TaskService
 * @pure
 *
 * This method can be called from within a task being run by
 * TaskService_runPendingTasks.
 *
 **************************************************************************/

void TaskService_addPeriodicTask(TaskService *self,
                                 Task        *task,
                                 long         delay,
                                 long         period) {

    self->vtable->addPeriodicTask(self, task, delay, period);
}






/**********************************************************************//**
 *
 * The Task is guaranteed to be no longer in use by the TaskService by
 * the time this method returns.
 *
 * @public @memberof TaskService
 * @pure
 *
 * This method can be called from within a task being run by
 * TaskService_runPendingTasks.
 *
 **************************************************************************/

void TaskService_cancelTask(TaskService *self,
                            Task        *task) {

    self->vtable->cancelTask(self, task);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

