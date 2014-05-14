/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef SYSTASKSERVICE_H
#define SYSTASKSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/tasks/TaskService.h>





    TaskService *SysTaskService_get(void);

    void SysTaskService_reset(void);





#ifdef __cplusplus
}
#endif

#endif
