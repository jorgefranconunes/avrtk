/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/ticks/CounterClock.h>





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(CounterClock) {
};





TEST(CounterClock, zeroAtStart) {

    CounterClock  counterClockData;
    CounterClock *counterClock = CounterClock_init(&counterClockData, 1, 1);
    Clock        *clock        = CounterClock_asClock(counterClock);

    LONGS_EQUAL(0, Clock_currentTimeMillis(clock));
}





TEST(CounterClock, oneByOne) {

    CounterClock  counterClockData;
    CounterClock *counterClock = CounterClock_init(&counterClockData, 1, 1);
    Clock        *clock        = CounterClock_asClock(counterClock);

    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 2L);
    LONGS_EQUAL(2L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 7L);
    LONGS_EQUAL(7L, Clock_currentTimeMillis(clock));
}





TEST(CounterClock, moreThanOne) {

    CounterClock  counterClockData;
    CounterClock *counterClock = CounterClock_init(&counterClockData, 3, 1);
    Clock        *clock        = CounterClock_asClock(counterClock);

    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 2L);
    LONGS_EQUAL(6L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 7L);
    LONGS_EQUAL(21L, Clock_currentTimeMillis(clock));
}





TEST(CounterClock, lessThanOne) {

    CounterClock  counterClockData;
    CounterClock *counterClock = CounterClock_init(&counterClockData, 1, 2);
    Clock        *clock        = CounterClock_asClock(counterClock);

    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 2L);
    LONGS_EQUAL(1L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 7L);
    LONGS_EQUAL(3L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 8L);
    LONGS_EQUAL(4L, Clock_currentTimeMillis(clock));
}





TEST(CounterClock, twoOverThree) {

    CounterClock  counterClockData;
    CounterClock *counterClock = CounterClock_init(&counterClockData, 2, 3);
    Clock        *clock        = CounterClock_asClock(counterClock);

    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 2L);
    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 7L);
    LONGS_EQUAL(4L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 8L);
    LONGS_EQUAL(4L, Clock_currentTimeMillis(clock));

    CounterClock_update(counterClock, 727L);
    LONGS_EQUAL(484L, Clock_currentTimeMillis(clock));
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

