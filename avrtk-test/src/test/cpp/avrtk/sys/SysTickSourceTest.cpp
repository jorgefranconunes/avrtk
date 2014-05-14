/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/sys/SysTickSource.h>
#include <avrtk/ticks/TickEventType.h>





static int   _counterValueIndex    = 0;
static long *_counterValueList     = NULL;
static int   _maxCounterValueIndex = 0;


static void initCounter(long *counterValueList,
                        int   counterValuesSize) {

    _counterValueIndex    = 0;
    _counterValueList     = counterValueList;
    _maxCounterValueIndex = counterValuesSize - 1;
}


static long getCounter() {

    long result = _counterValueList[_counterValueIndex];

    if ( _counterValueIndex < _maxCounterValueIndex ) {
        ++_counterValueIndex;
    }

    return result;
}





static void testCheckEvents(long counterValueList[],
                            int  counterValuesSize) {

    SysTickSource_reset();
    initCounter(counterValueList, counterValuesSize);
    SysTickSource_init(getCounter, 1, 1);

    EventSource *eventSource   = SysTickSource_get();
    Clock       *clock         = SysTickSource_getClock();
    EventType   *tickEventType = TickEventType_get();
    CHECK( NULL != eventSource );

    int  checkCount      = 0;
    long previousCounter = 0L;

    for ( int i=0, size=counterValuesSize; i<size; ++i ) {
        long   currentCounter = counterValueList[i];
        Event *event          = EventSource_poll(eventSource);

        if ( currentCounter == previousCounter ) {
            CHECK( NULL == event );
        } else {
            CHECK( NULL != event );
            
            EventType *eventType = Event_getEventType(event);
            POINTERS_EQUAL(tickEventType, eventType);
        }

        CHECK_EQUAL( currentCounter, Clock_currentTimeMillis(clock) );

        previousCounter = currentCounter;
        ++checkCount;
    }

    CHECK_EQUAL(counterValuesSize, checkCount);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(SysTickSource) {


    


    void setup() {
    }


    void teardown() {
    }


};




IGNORE_TEST(SysTickSource, getWihoutInit) {

    SysTickSource_reset();
    SysTickSource_get();
}





TEST(SysTickSource, noEvents01) {
    long counterValueList[] = { 0 };
    int  counterValuesSize  = 1;
    testCheckEvents(counterValueList, counterValuesSize);
}


TEST(SysTickSource, noEvents02) {
    long counterValueList[] = { 0, 0 };
    int  counterValuesSize  = 2;
    testCheckEvents(counterValueList, counterValuesSize);
}


TEST(SysTickSource, noEvents03) {
    long counterValueList[] = { 0, 0, 0, 0, 0 };
    int  counterValuesSize  = 5;
    testCheckEvents(counterValueList, counterValuesSize);
}





TEST(SysTickSource, manyEvents01) {
    long counterValueList[] = { 0, 1 };
    int  counterValuesSize  = 2;
    testCheckEvents(counterValueList, counterValuesSize);
}


TEST(SysTickSource, manyEvents02) {
    long counterValueList[] = { 1, 1 };
    int  counterValuesSize  = 2;
    testCheckEvents(counterValueList, counterValuesSize);
}


TEST(SysTickSource, manyEvents03) {
    long counterValueList[] = { 1, 2 };
    int  counterValuesSize  = 2;
    testCheckEvents(counterValueList, counterValuesSize);
}


TEST(SysTickSource, manyEvents04) {
    long counterValueList[] = { 1, 1, 2 };
    int  counterValuesSize  = 3;
    testCheckEvents(counterValueList, counterValuesSize);
}


TEST(SysTickSource, manyEvents05) {
    long counterValueList[] = { 1, 2, 2 };
    int  counterValuesSize  = 3;
    testCheckEvents(counterValueList, counterValuesSize);
}


TEST(SysTickSource, manyEvents06) {
    long counterValueList[] = { 1, 7, 7 };
    int  counterValuesSize  = 3;
    testCheckEvents(counterValueList, counterValuesSize);
}


TEST(SysTickSource, manyEvents07) {
    long counterValueList[] = { 1, 2, 2, 10, 11, 20, 20, 20, 50, 52 };
    int  counterValuesSize  = 10;
    testCheckEvents(counterValueList, counterValuesSize);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

