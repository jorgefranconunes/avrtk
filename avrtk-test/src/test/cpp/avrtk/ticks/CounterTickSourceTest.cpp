/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/ticks/CounterTickSource.h>
#include <avrtk/ticks/TickEventType.h>





static long _myTickCounter = 0L;


static long getMyTickCounter() {
    return _myTickCounter;
}

static void setMyTickCounter(long counter) {
    _myTickCounter = counter;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(CounterTickSource) {

    EventType *tickEventType;

    CounterTickSource  counterTickSourceData;
    CounterTickSource *counterTickSource;
    EventSource       *eventSource;
    Clock             *clock;


    void setup() {

        tickEventType = TickEventType_get();
    }


    void teardown() {
    }





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

    void prepare(int incrFactorN,
                 int incrFactorD) {

        counterTickSource =
            CounterTickSource_init(&counterTickSourceData,
                                   &getMyTickCounter,
                                   incrFactorN,
                                   incrFactorD);

        eventSource = CounterTickSource_asEventSource(counterTickSource);
        clock       = CounterTickSource_getClock(counterTickSource);

        setMyTickCounter(0L);
    }





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

    void assertHasTickEvent() {

        Event *event = EventSource_poll(eventSource);

        CHECK( event != NULL);
        POINTERS_EQUAL(tickEventType, Event_getEventType(event));
    }





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

    void assertHasNoEvent() {

        POINTERS_EQUAL(NULL, EventSource_poll(eventSource));
    }


};





TEST(CounterTickSource, zeroAtStart) {

    prepare(1, 1);

    assertHasNoEvent();
    LONGS_EQUAL(0, Clock_currentTimeMillis(clock));
}





TEST(CounterTickSource, oneByOne) {

    prepare(1, 1);

    assertHasNoEvent();
    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    setMyTickCounter(2L);
    assertHasTickEvent();
    LONGS_EQUAL(2L, Clock_currentTimeMillis(clock));

    assertHasNoEvent();
    LONGS_EQUAL(2L, Clock_currentTimeMillis(clock));

    setMyTickCounter(7L);
    assertHasTickEvent();
    LONGS_EQUAL(7L, Clock_currentTimeMillis(clock));
}





TEST(CounterTickSource, moreThanOne) {

    prepare(3, 1);

    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    setMyTickCounter(2L);
    assertHasTickEvent();
    LONGS_EQUAL(6L, Clock_currentTimeMillis(clock));

    setMyTickCounter(7L);
    assertHasTickEvent();
    LONGS_EQUAL(21L, Clock_currentTimeMillis(clock));
}





TEST(CounterTickSource, lessThanOne) {

    prepare(1, 2);

    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    setMyTickCounter(2L);
    assertHasTickEvent();
    LONGS_EQUAL(1L, Clock_currentTimeMillis(clock));

    setMyTickCounter(7L);
    assertHasTickEvent();
    LONGS_EQUAL(3L, Clock_currentTimeMillis(clock));

    setMyTickCounter(8L);
    assertHasTickEvent();
    LONGS_EQUAL(4L, Clock_currentTimeMillis(clock));

    setMyTickCounter(9L);
    assertHasTickEvent();
    LONGS_EQUAL(4L, Clock_currentTimeMillis(clock));
}





TEST(CounterTickSource, twoOverThree) {

    prepare(2, 3);

    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    setMyTickCounter(2L);
    assertHasTickEvent();
    LONGS_EQUAL(0L, Clock_currentTimeMillis(clock));

    setMyTickCounter(7L);
    assertHasTickEvent();
    LONGS_EQUAL(4L, Clock_currentTimeMillis(clock));

    setMyTickCounter(8L);
    assertHasTickEvent();
    LONGS_EQUAL(4L, Clock_currentTimeMillis(clock));

    setMyTickCounter(727L);
    assertHasTickEvent();
    LONGS_EQUAL(484L, Clock_currentTimeMillis(clock));
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

