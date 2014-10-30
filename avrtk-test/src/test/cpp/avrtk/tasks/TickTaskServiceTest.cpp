/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/events/Event.h>
#include <avrtk/tasks/TickTaskService.h>
#include <avrtk/ticks/TickEventType.h>

#include <avrtk/events/TestEventSource.h>
#include <avrtk/ticks/TestClock.h>
#include <avrtk/tasks/TestTask.h>





static int tickCountList[] = { 1000 };





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(TaskService) {


    Event  tickEventData;
    Event *tickEvent;

    TestEventSource  tickEventSourceData;
    TestEventSource *tickEventSource;

    TestClock     testClockData;
    TestClock    *testClock;

    EventManager  eventManagerData;
    EventManager *eventManager;

    TickTaskService  taskServiceData;
    TickTaskService *tickTaskService;
    TaskService     *taskService;





    void setup() {

        tickEvent = Event_init(&tickEventData, TickEventType_get());

        tickEventSource =
            TestEventSource_init(&tickEventSourceData,
                                 tickEvent,
                                 tickCountList,
                                 1);

        testClock = TestClock_init(&testClockData);

        eventManager = EventManager_init(&eventManagerData);
        EventManager_addSource(eventManager,
                               TestEventSource_asEventSource(tickEventSource));

        tickTaskService =
            TickTaskService_init(&taskServiceData,
                                 eventManager,
                                 TestClock_asClock(testClock));
        taskService = TickTaskService_asTaskService(tickTaskService);
        TaskService_start(taskService);
    }





    void teardown() {
    }

};





TEST(TaskService, doInit) {

    CHECK_EQUAL(0, TestClock_time(testClock));
}





TEST(TaskService, addOneTask) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskService_addTask(taskService, TestTask_asTask(&testTask), 10);
}





TEST(TaskService, addTaskNoRun) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskService_addTask(taskService, TestTask_asTask(&testTask), 10);
    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));

    EventManager_sweep(eventManager);
    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));
}





TEST(TaskService, addTaskRunOnTime) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskService_addTask(taskService, TestTask_asTask(&testTask), 10);

    TestClock_addTime(testClock, 10);

    EventManager_sweep(eventManager);
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));

    EventManager_sweep(eventManager);
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));
}





TEST(TaskService, addTaskRunAfterTime) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskService_addTask(taskService, TestTask_asTask(&testTask), 10);

    TestClock_addTime(testClock, 15);

    EventManager_sweep(eventManager);
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 15);

    EventManager_sweep(eventManager);
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));
}





TEST(TaskService, cancelTask) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskService_addTask(taskService, TestTask_asTask(&testTask), 10);
    TaskService_cancelTask(taskService, TestTask_asTask(&testTask));

    TestClock_addTime(testClock, 15);
    EventManager_sweep(eventManager);

    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));
}





TEST(TaskService, addPeriodicTask) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskService_addPeriodicTask(taskService,
                                TestTask_asTask(&testTask),
                                5,
                                10);

    EventManager_sweep(eventManager);
    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 10);

    EventManager_sweep(eventManager);
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 10);

    EventManager_sweep(eventManager);
    CHECK_EQUAL(2, TestTask_getCallCount(&testTask));
}





TEST(TaskService, cancelPeriodicTask) {

    TestTask testTask;
    TestTask_init(&testTask);

    TaskService_addPeriodicTask(taskService,
                                TestTask_asTask(&testTask),
                                5,
                                10);

    EventManager_sweep(eventManager);
    CHECK_EQUAL(0, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 10);

    EventManager_sweep(eventManager);
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));

    TestClock_addTime(testClock, 10);

    TaskService_cancelTask(taskService, TestTask_asTask(&testTask));

    EventManager_sweep(eventManager);
    CHECK_EQUAL(1, TestTask_getCallCount(&testTask));
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

