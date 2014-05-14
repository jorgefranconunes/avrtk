/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef TESTCLOCK_H
#define TESTCLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/ticks/Clock.h>





    typedef struct TestClockStruct TestClock;

    struct TestClockStruct {
        Clock base;
        long  time;
    };

    TestClock *TestClock_init(TestClock *self);

    void TestClock_setTime(TestClock *self, long time);

    void TestClock_addTime(TestClock *self, long interval);

    long TestClock_time(TestClock *self);

    Clock *TestClock_asClock(TestClock *self);





#ifdef __cplusplus
}
#endif

#endif
