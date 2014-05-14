/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/sys/SysEventManager.h>
#include <avrtk/sys/SysTaskService.h>
#include <avrtk/sys/SysTickSource.h>

#include <avrtk/tasks/TestTask.h>





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

    return result;
}


static void incrCounter() {

    if ( _counterValueIndex < _maxCounterValueIndex ) {
        ++_counterValueIndex;
    }
}





static void testDoSweeps(long counterValueList[],
                         int  counterValuesSize) {

    EventManager *eventManager = SysEventManager_get();
    Clock        *clock        = SysTickSource_getClock();

    int  sweepCount      = 0;
    long previousCounter = 0L;

    for ( int i=0, size=counterValuesSize; i<size; ++i ) {
        long   currentCounter = counterValueList[i];

        EventManager_sweep(eventManager);

        CHECK_EQUAL( currentCounter, Clock_currentTimeMillis(clock) );

        previousCounter = currentCounter;
        ++sweepCount;
        incrCounter();
    }

    CHECK_EQUAL(counterValuesSize, sweepCount);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void testNonRecursiveTask(long counterValueList[],
                                 int  counterValuesSize,
                                 int  expectedCallCount,
                                 long delay) {

    SysTaskService_reset();
    SysTickSource_reset();
    SysEventManager_reset();

    initCounter(counterValueList, counterValuesSize);
    SysTickSource_init(getCounter, 1, 1);

    TestTask     testTaskData;
    TestTask    *testTask    = TestTask_init(&testTaskData);
    TaskService *taskService = SysTaskService_get();

    TaskService_addTask(taskService, TestTask_asTask(testTask), delay);
    testDoSweeps(counterValueList, counterValuesSize);

    CHECK_EQUAL(expectedCallCount, TestTask_getCallCount(testTask));
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void testRecursiveTask(long counterValueList[],
                              int  counterValuesSize,
                              int  expectedCallCount,
                              long delay,
                              long period) {

    SysTaskService_reset();
    SysTickSource_reset();
    SysEventManager_reset();

    initCounter(counterValueList, counterValuesSize);
    SysTickSource_init(getCounter, 1, 1);

    TestTask     testTaskData;
    TestTask    *testTask    = TestTask_init(&testTaskData);
    TaskService *taskService = SysTaskService_get();

    TaskService_addPeriodicTask(taskService,
                                TestTask_asTask(testTask),
                                delay,
                                period);
    testDoSweeps(counterValueList, counterValuesSize);

    CHECK_EQUAL(expectedCallCount, TestTask_getCallCount(testTask));
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(SysTaskService) {


    


    void setup() {
    }


    void teardown() {
    }


};





TEST(SysTaskService, noCalls01) {
    long counterValueList[] = { 0 };
    int  counterValuesSize  = 1;
    testNonRecursiveTask(counterValueList, counterValuesSize, 0, 0);
}


TEST(SysTaskService, noCalls02) {
    long counterValueList[] = { 0, 0 };
    int  counterValuesSize  = 2;
    testNonRecursiveTask(counterValueList, counterValuesSize, 0, 2);
}


TEST(SysTaskService, noCalls03) {
    long counterValueList[] = { 0, 5 };
    int  counterValuesSize  = 2;
    testNonRecursiveTask(counterValueList, counterValuesSize, 0, 10);
}


TEST(SysTaskService, noCalls04) {
    long counterValueList[] = { 0, 2, 4, 6, 8 };
    int  counterValuesSize  = 5;
    testNonRecursiveTask(counterValueList, counterValuesSize, 0, 10);
}





TEST(SysTaskService, oneCall01) {
    long counterValueList[] = { 0, 1 };
    int  counterValuesSize  = 2;
    testNonRecursiveTask(counterValueList, counterValuesSize,1, 0);
}


TEST(SysTaskService, oneCall02) {
    long counterValueList[] = { 1, 1 };
    int  counterValuesSize  = 2;
    testNonRecursiveTask(counterValueList, counterValuesSize, 1, 0);
}


TEST(SysTaskService, oneCall03) {
    long counterValueList[] = { 1, 2 };
    int  counterValuesSize  = 2;
    testNonRecursiveTask(counterValueList, counterValuesSize, 1, 0);
}


TEST(SysTaskService, oneCall04) {
    long counterValueList[] = { 1, 2 };
    int  counterValuesSize  = 2;
    testNonRecursiveTask(counterValueList, counterValuesSize, 1, 1);
}


TEST(SysTaskService, oneCall05) {
    long counterValueList[] = { 1, 2 };
    int  counterValuesSize  = 2;
    testNonRecursiveTask(counterValueList, counterValuesSize, 1, 2);
}


TEST(SysTaskService, oneCall06) {
    long counterValueList[] = { 1, 5, 12 };
    int  counterValuesSize  = 3;
    testNonRecursiveTask(counterValueList, counterValuesSize, 1, 7);
}


TEST(SysTaskService, oneCall07) {
    long counterValueList[] = { 1, 5, 5 };
    int  counterValuesSize  = 3;
    testNonRecursiveTask(counterValueList, counterValuesSize, 1, 3);
}


TEST(SysTaskService, oneCall08) {
    long counterValueList[] = { 2, 2, 7 };
    int  counterValuesSize  = 3;
    testNonRecursiveTask(counterValueList, counterValuesSize, 1, 6);
}


TEST(SysTaskService, oneCall09) {
    long counterValueList[] = { 1, 2, 2, 10, 11, 20, 20, 20, 50, 52 };
    int  counterValuesSize  = 10;
    testNonRecursiveTask(counterValueList, counterValuesSize, 1, 8);
}





TEST(SysTaskService, manyCalls01) {
    long counterValueList[] = { 0, 1 };
    int  counterValuesSize  = 2;
    testRecursiveTask(counterValueList, counterValuesSize, 1, 0, 2);
}


TEST(SysTaskService, manyCalls02) {
    long counterValueList[] = { 1, 1 };
    int  counterValuesSize  = 2;
    testRecursiveTask(counterValueList, counterValuesSize, 1, 1, 1);
}


TEST(SysTaskService, manyCalls03) {
    long counterValueList[] = { 1, 2 };
    int  counterValuesSize  = 2;
    testRecursiveTask(counterValueList, counterValuesSize, 3, 0, 1);
}


TEST(SysTaskService, manyCalls04) {
    long counterValueList[] = { 1, 2 };
    int  counterValuesSize  = 2;
    testRecursiveTask(counterValueList, counterValuesSize, 1, 1, 2);
}


TEST(SysTaskService, manyCalls05) {
    long counterValueList[] = { 1, 2 };
    int  counterValuesSize  = 2;
    testRecursiveTask(counterValueList, counterValuesSize, 1, 2, 1);
}


TEST(SysTaskService, manyCalls06) {
    long counterValueList[] = { 1, 5, 12 };
    int  counterValuesSize  = 3;
    testRecursiveTask(counterValueList, counterValuesSize, 3, 7, 2);
}


TEST(SysTaskService, manyCalls07) {
    long counterValueList[] = { 1, 5, 5 };
    int  counterValuesSize  = 3;
    testRecursiveTask(counterValueList, counterValuesSize, 2, 3, 2);
}


TEST(SysTaskService, manyCalls08) {
    long counterValueList[] = { 2, 2, 7 };
    int  counterValuesSize  = 3;
    testRecursiveTask(counterValueList, counterValuesSize, 1, 6, 2);
}


TEST(SysTaskService, manyCalls09) {
    long counterValueList[] = { 1, 2, 2, 10, 11, 20, 20, 20, 50, 52 };
    int  counterValuesSize  = 10;
    testRecursiveTask(counterValueList, counterValuesSize, 14, 0, 4);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

