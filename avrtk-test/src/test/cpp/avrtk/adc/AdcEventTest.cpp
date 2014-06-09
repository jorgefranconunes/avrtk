/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/adc/AdcEvent.h>
#include <avrtk/adc/AdcEventType.h>





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(AdcEvent) {


    void setup() {
        // Nothing to do.
    }


    void teardown() {
        // Nothing to do.
    }

};





TEST(AdcEvent, doInit) {

    AdcEvent  adcEventData;
    AdcEvent *adcEvent = AdcEvent_init(&adcEventData, 123, 456);
    
    CHECK ( adcEvent != NULL );
}





TEST(AdcEvent, getSample) {

    AdcEvent   adcEventData;
    AdcEvent  *adcEvent = AdcEvent_init(&adcEventData, 123, 456);
    AdcSample *sample   = AdcEvent_getSample(adcEvent);
    
    CHECK ( sample != NULL );
    CHECK_EQUAL( 123, AdcSample_getChannelId(sample) );
    CHECK_EQUAL( 456, AdcSample_getValue(sample) );
}





TEST(AdcEvent, asEvent) {

    AdcEvent  adcEventData;
    AdcEvent *adcEvent = AdcEvent_init(&adcEventData, 123, 456);
    Event    *event    = AdcEvent_asEvent(adcEvent);

    CHECK ( event != NULL );
    POINTERS_EQUAL( AdcEventType_get(), Event_getEventType(event) );
}





TEST(AdcEvent, fromEvent) {

    AdcEvent  adcEventData;
    AdcEvent *adcEvent = AdcEvent_init(&adcEventData, 123, 456);
    Event    *event    = AdcEvent_asEvent(adcEvent);

    POINTERS_EQUAL( adcEvent, AdcEvent_fromEvent(event) );
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

