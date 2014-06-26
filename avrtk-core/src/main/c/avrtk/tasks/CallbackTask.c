/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/tasks/CallbackTask.h
 *
 * @brief Definition of the CallbackTask class methods.
 *
 **************************************************************************/

#include <avrtk/tasks/CallbackTask.h>





/**********************************************************************//**
 *
 * @class CallbackTask avrtk/tasks/CallbackTask.h <avrtk/tasks/CallbackTask.h>
 *
 * @implements Task
 *
 * @brief A concrete Task whose work is performed by a function.
 *
 **************************************************************************/





static TaskInterface interface = {
    .run = &CallbackTask_run
};





/**********************************************************************//**
 *
 * Initializes a CallbackTask object.
 *
 * @public @memberof CallbackTask
 *
 * @param self Reference to the CallbackTask object to be initialized.
 *
 * @param callback The function that will be called when the task is
 * run.
 *
 **************************************************************************/

CallbackTask *CallbackTask_init(CallbackTask *self,
                                void        (*callback)(void)) {

    self->base.vtable = &interface;
    self->callback    = callback;

    return self;
}





/**********************************************************************//**
 *
 * Casts a CallbackTask reference to a Task reference.
 *
 * @public @memberof CallbackTask
 *
 * @param self 
 *
 * @return A reference to the same CallbackTask object this method was
 * called for.
 *
 **************************************************************************/

Task *CallbackTask_asTask(CallbackTask *self) {

    Task *result = (Task *)self;

    return result;
}





/**********************************************************************//**
 *
 * Runs the task. The function given at initialization time is invoked.
 *
 * @public @memberof CallbackTask
 *
 * This is the implementation of method Task_run().
 *
 * @param baseSelf Reference to the Task to be run. This must actually
 * be a reference to a CallbackTask instance.
 *
 **************************************************************************/

void CallbackTask_run(Task *baseSelf) {

    CallbackTask *self = (CallbackTask *)baseSelf;

    self->callback();
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

