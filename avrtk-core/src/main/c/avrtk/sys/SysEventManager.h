/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef SYSEVENTMANAGER_H
#define SYSEVENTMANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/EventManager.h>





    EventManager *SysEventManager_get(void);

    void SysEventManager_start(void);

    void SysEventManager_reset(void);





#ifdef __cplusplus
}
#endif

#endif
