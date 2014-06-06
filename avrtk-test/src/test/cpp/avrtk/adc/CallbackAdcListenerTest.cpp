/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/adc/CallbackAdcListener.h>





static int        _myCounter = 0;
static AdcSample  _mySampleData;
static AdcSample *_mySample = NULL;


static void testCallback(AdcSample *sample) {

    ++_myCounter;
    _mySample = AdcSample_initFromSample(&_mySampleData, sample);
}


static void checkSamples(AdcSample *expected,
                         AdcSample *actual) {

    if ( NULL == expected ) {
        POINTERS_EQUAL(NULL, actual);
    } else {
        CHECK_EQUAL(AdcSample_getChannelId(expected),
                    AdcSample_getChannelId(actual));

        CHECK_EQUAL(AdcSample_getValue(expected),
                    AdcSample_getValue(actual));
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(CallbackAdcListener) {


    void setup() {

        _myCounter= 0;
        _mySample = NULL;
    }


    void teardown() {
    }

};





TEST(CallbackAdcListener, doInit) {

    CallbackAdcListener listenerData;

    CallbackAdcListener_init(&listenerData, &testCallback);

    CHECK_EQUAL(0, _myCounter);
    POINTERS_EQUAL(NULL, _mySample);
}





TEST(CallbackAdcListener, asAdcListener) {

    CallbackAdcListener  callbackAdcListenerData;
    CallbackAdcListener *callbackAdcListener =
        CallbackAdcListener_init(&callbackAdcListenerData, &testCallback);

    CHECK_EQUAL(0, _myCounter);
    checkSamples(NULL, _mySample);

    AdcListener *listener =
        CallbackAdcListener_asAdcListener(callbackAdcListener);
    CHECK_EQUAL(0, _myCounter);
    checkSamples(NULL, _mySample);
}





TEST(CallbackAdcListener, notifyOnce) {

    CallbackAdcListener  callbackAdcListenerData;
    CallbackAdcListener *callbackAdcListener =
        CallbackAdcListener_init(&callbackAdcListenerData, &testCallback);
    AdcListener         *adcListener =
        CallbackAdcListener_asAdcListener(callbackAdcListener);

    CHECK_EQUAL(0, _myCounter);
    checkSamples(NULL, _mySample);


    AdcSample  demoSampleData;
    AdcSample *demoSample = AdcSample_init(&demoSampleData, 23, 24);

    AdcListener_notify(adcListener, demoSample);
    CHECK_EQUAL(1, _myCounter);
    checkSamples(demoSample, _mySample);
}





TEST(CallbackAdcListener, notifyTwice) {

    CallbackAdcListener  callbackAdcListenerData;
    CallbackAdcListener *callbackAdcListener =
        CallbackAdcListener_init(&callbackAdcListenerData, &testCallback);
    AdcListener         *adcListener =
        CallbackAdcListener_asAdcListener(callbackAdcListener);

    CHECK_EQUAL(0, _myCounter);
    checkSamples(NULL, _mySample);


    AdcSample  demoSampleData;
    AdcSample *demoSample = AdcSample_init(&demoSampleData, 23, 24);

    AdcListener_notify(adcListener, demoSample);
    CHECK_EQUAL(1, _myCounter);
    checkSamples(demoSample, _mySample);


    demoSample = AdcSample_init(&demoSampleData, 45, 46);
    AdcListener_notify(adcListener, demoSample);
    CHECK_EQUAL(2, _myCounter);
    checkSamples(demoSample, _mySample);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

