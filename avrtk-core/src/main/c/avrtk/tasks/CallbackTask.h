/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef CALLBACKTASK_H
#define CALLBACKTASK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/tasks/Task.h>





    typedef struct CallbackTaskStruct CallbackTask;

    struct CallbackTaskStruct {
        Task   base;
        void (*callback)(void);
    };

    void CallbackTask_init(CallbackTask *self,
                           void        (*callback)(void));

    Task *CallbackTask_build(CallbackTask *self,
                             void        (*callback)(void));

    Task *CallbackTask_asTask(CallbackTask *self);





#ifdef __cplusplus
}
#endif

#endif

