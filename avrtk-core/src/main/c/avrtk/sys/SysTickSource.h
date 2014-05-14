/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef SYSTICKSOURCE_H
#define SYSTICKSOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/EventSource.h>
#include <avrtk/ticks/Clock.h>





    void SysTickSource_init(long (*tickCountGetter)(void),
                            int    incrementFactorN,
                            int    incrementFactorD);

    Clock *SysTickSource_getClock(void);

    EventSource *SysTickSource_get(void);

    void SysTickSource_reset(void);





#ifdef __cplusplus
}
#endif

#endif
