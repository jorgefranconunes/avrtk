/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/tasks/CallbackTask.h>





static void CallbackTask_run(Task *baseSelf);

static TaskInterface interface = {
    .run = &CallbackTask_run
};





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

CallbackTask *CallbackTask_init(CallbackTask *self,
                                void        (*callback)(void)) {

    self->base.vtable = &interface;
    self->callback    = callback;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

Task *CallbackTask_asTask(CallbackTask *self) {

    Task *result = (Task *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void CallbackTask_run(Task *baseSelf) {

    CallbackTask *self = (CallbackTask *)baseSelf;

    self->callback();
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

