/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/tasks/CallbackTask.h>





static int _counter = 0;


static void testCallback() {

    ++_counter;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(CallbackTask) {


    void setup() {

        _counter = 0;
    }


    void teardown() {
    }

};





TEST(CallbackTask, doInit) {

    CallbackTask taskData;

    CallbackTask_init(&taskData, &testCallback);

    CHECK_EQUAL(0, _counter);
}





TEST(CallbackTask, asTask) {

    CallbackTask taskData;

    CallbackTask_init(&taskData, &testCallback);
    CHECK_EQUAL(0, _counter);

    Task *task = CallbackTask_asTask(&taskData);
    CHECK_EQUAL(0, _counter);

    Task_run(task);
    CHECK_EQUAL(1, _counter);
}





TEST(CallbackTask, build) {

    CallbackTask taskData;
    Task        *task = CallbackTask_build(&taskData, &testCallback);

    CHECK_EQUAL(0, _counter);
    Task_run(task);
    CHECK_EQUAL(1, _counter);
}





TEST(CallbackTask, runTwice) {

    CallbackTask taskData;
    Task        *task = CallbackTask_build(&taskData, &testCallback);

    CHECK_EQUAL(0, _counter);
    Task_run(task);
    CHECK_EQUAL(1, _counter);
    Task_run(task);
    CHECK_EQUAL(2, _counter);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

