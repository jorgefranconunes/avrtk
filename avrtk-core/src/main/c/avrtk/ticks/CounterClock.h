/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef COUNTERCLOCK_H
#define COUNTERCLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/ticks/Clock.h>





    typedef struct CounterClockStruct CounterClock;

    struct CounterClockStruct {
        Clock base;
        int   incrFactorN;
        int   incrFactorD;
        long  ticks;
        long  time;
    };

    CounterClock *CounterClock_init(CounterClock *self,
                                    int           incrementFactorN,
                                    int           incrementFactorD);

    void CounterClock_update(CounterClock *self,
                             long          currentTickCount);

    Clock *CounterClock_asClock(CounterClock *self);





#ifdef __cplusplus
}
#endif

#endif
