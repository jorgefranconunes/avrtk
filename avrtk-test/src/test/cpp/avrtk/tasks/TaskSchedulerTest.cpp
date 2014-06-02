/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/tasks/TaskScheduler.h>

#include <avrtk/ticks/TestClock.h>
#include <avrtk/tasks/TestTask.h>





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(TaskScheduler) {


    TestClock      testClockData;
    TestClock     *testClock;
    TaskScheduler  schedulerData;
    TaskScheduler *scheduler;


    void setup() {

        testClock =
            TestClock_init(&testClockData);
        scheduler =
            TaskScheduler_init(&schedulerData, TestClock_asClock(testClock));
    }


    void teardown() {
    }

};





TEST(TaskScheduler, doInit) {

    CHECK_EQUAL(0, TestClock_time(testClock));
    CHECK_EQUAL(0, TaskScheduler_getPendingCount(scheduler));
}





TEST(TaskScheduler, checkTestClock) {

    Clock *clock = TestClock_asClock(testClock);

    CHECK_EQUAL(0, TestClock_time(testClock));

    TestClock_setTime(testClock, 1234);
    CHECK_EQUAL(1234, TestClock_time(testClock));
    CHECK_EQUAL(1234, Clock_currentTimeMillis(clock));

    TestClock_addTime(testClock, 321);
    CHECK_EQUAL(1555, TestClock_time(testClock));
    CHECK_EQUAL(1555, Clock_currentTimeMillis(clock));
}





TEST(TaskScheduler, addOneTask) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskScheduler_addTask(scheduler, TestTask_asTask(&testTask), 10);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));
}





TEST(TaskScheduler, addTaskNoRun) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskScheduler_addTask(scheduler, TestTask_asTask(&testTask), 10);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));
}





TEST(TaskScheduler, addTaskRunOnTime) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskScheduler_addTask(scheduler, TestTask_asTask(&testTask), 10);

    TestClock_addTime(testClock, 10);

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(0, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(0, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));
}





TEST(TaskScheduler, addTaskRunAfterTime) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskScheduler_addTask(scheduler, TestTask_asTask(&testTask), 10);

    TestClock_addTime(testClock, 15);

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(0, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 15);

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(0, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));
}





TEST(TaskScheduler, cancelTask) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskScheduler_addTask(scheduler, TestTask_asTask(&testTask), 10);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));

    TaskScheduler_cancelTask(scheduler, TestTask_asTask(&testTask));
    CHECK_EQUAL(0, TaskScheduler_getPendingCount(scheduler));
}





TEST(TaskScheduler, addPeriodicTask) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskScheduler_addPeriodicTask(scheduler,
                                  TestTask_asTask(&testTask),
                                  5,
                                  10);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 10);

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 10);

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(2, TestTask_getCallCount(&testTask));
}





TEST(TaskScheduler, cancelPeriodicTask) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskScheduler_addPeriodicTask(scheduler,
                                  TestTask_asTask(&testTask),
                                  5,
                                  10);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 10);

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(1, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 10);

    TaskScheduler_cancelTask(scheduler, TestTask_asTask(&testTask));
    CHECK_EQUAL(0, TaskScheduler_getPendingCount(scheduler));

    TaskScheduler_runPendingTasks(scheduler);
    CHECK_EQUAL(0, TaskScheduler_getPendingCount(scheduler));
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

