/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/tasks/Task.h
 *
 * @brief Definition of the Task interface methods.
 *
 **************************************************************************/

#include <avrtk/tasks/Task.h>





/**********************************************************************//**
 *
 * @interface Task avrtk/tasks/Task.h <avrtk/tasks/Task.h>
 * @ingroup avrtk_tasks
 *
 * @brief A piece of work intended to be run by a TaskService.
 *
 **************************************************************************/





/**********************************************************************//**
 *
 * Executes the task.
 *
 * @public @memberof Task
 * @pure
 *
 * @param self Reference to the Task object to be run.
 *
 **************************************************************************/

void Task_run(Task *self) {

    self->vtable->run(self);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

