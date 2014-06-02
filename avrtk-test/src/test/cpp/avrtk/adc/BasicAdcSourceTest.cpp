/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/adc/AdcEventType.h>
#include <avrtk/adc/BasicAdcSource.h>





const int CHANNEL1_ID = 4;
const int CHANNEL2_ID = 1;


static bool     startMyAdc(int channel);
static bool     isMyAdcCompleted(void);
static uint16_t getMyLatestAdcValue(void);

static void resetMyAdc(void);
static void setMyAdcValue(uint16_t adcValue);

static bool     _isAdcStarted   = false;
static bool     _isAdcCompleted = false;
static uint16_t _adcValue       = 0;







/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static bool startMyAdc(int channel) {

    CHECK ( !_isAdcStarted || _isAdcCompleted);

    _isAdcStarted   = true;
    _isAdcCompleted = false;
    _adcValue       = 0;

    return true;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static bool isMyAdcCompleted() {

    CHECK ( _isAdcStarted || _isAdcCompleted);

    return _isAdcCompleted;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static uint16_t getMyLatestAdcValue(void) {

    CHECK ( _isAdcCompleted );

    return _adcValue;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void resetMyAdc() {

    _isAdcStarted   = false;
    _isAdcCompleted = false;
    _adcValue       = 0;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void setMyAdcValue(uint16_t adcValue) {

    _isAdcStarted   = false;
    _isAdcCompleted = true;
    _adcValue       = adcValue;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(BasicAdcSource) {


    BasicAdcSource  _basicAdcSourceData;
    BasicAdcSource *_basicAdcSource;
    AdcSource      *_adcSource;
    EventSource    *_eventSource;


    void setup() {

        resetMyAdc();

        _basicAdcSource =
            BasicAdcSource_init(&_basicAdcSourceData,
                                &startMyAdc,
                                &isMyAdcCompleted,
                                &getMyLatestAdcValue);
        _adcSource   = BasicAdcSource_asAdcSource(_basicAdcSource);
        _eventSource = AdcSource_asEventSource(_adcSource);
    }


    void teardown() {
    }





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

    void assertHasAdcEvent() {

        EventType   *adcEventType = AdcEventType_get();
        Event       *event        = EventSource_poll(_eventSource);

        CHECK( event != NULL);
        POINTERS_EQUAL(adcEventType, Event_getEventType(event));
    }





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

    void assertHasAdcEventWithSample(int      channelId,
                                     uint16_t value) {

        EventType   *adcEventType = AdcEventType_get();
        Event       *event        = EventSource_poll(_eventSource);

        CHECK( event != NULL);
        POINTERS_EQUAL(adcEventType, Event_getEventType(event));

        AdcEvent  *adcEvent = AdcEvent_fromEvent(event);
        AdcSample *sample   = AdcEvent_getSample(adcEvent);

        CHECK_EQUAL(channelId, AdcSample_getChannelId(sample));
        CHECK_EQUAL(value, AdcSample_getValue(sample))
    }





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

    void assertHasNoEvent() {

        POINTERS_EQUAL(NULL, EventSource_poll(_eventSource));
    }


};





TEST(BasicAdcSource, noEventAtStart) {

    assertHasNoEvent();
}





TEST(BasicAdcSource, noEventWithOneChannel) {

    AdcSourceChannel  sourceChannelData;
    AdcSourceChannel *sourceChannel =
        AdcSourceChannel_init(&sourceChannelData, CHANNEL1_ID);

    AdcSource_addSourceChannel(_adcSource, sourceChannel);

    assertHasNoEvent();
}





TEST(BasicAdcSource, noEventWithOneChannelTwice) {

    AdcSourceChannel  sourceChannelData;
    AdcSourceChannel *sourceChannel =
        AdcSourceChannel_init(&sourceChannelData, CHANNEL1_ID);

    AdcSource_addSourceChannel(_adcSource, sourceChannel);

    assertHasNoEvent();
    assertHasNoEvent();
}





TEST(BasicAdcSource, oneEventOneChannel) {

    AdcSourceChannel  sourceChannelData;
    AdcSourceChannel *sourceChannel =
        AdcSourceChannel_init(&sourceChannelData, CHANNEL1_ID);

    AdcSource_addSourceChannel(_adcSource, sourceChannel);
    assertHasNoEvent();

    setMyAdcValue(234);
    assertHasAdcEventWithSample(CHANNEL1_ID, 234);
    CHECK( _isAdcStarted );
    assertHasNoEvent();
}





TEST(BasicAdcSource, twoEventsOneChannel) {

    AdcSourceChannel  sourceChannelData;
    AdcSourceChannel *sourceChannel =
        AdcSourceChannel_init(&sourceChannelData, CHANNEL1_ID);

    AdcSource_addSourceChannel(_adcSource, sourceChannel);
    assertHasNoEvent();

    setMyAdcValue(234);
    assertHasAdcEventWithSample(CHANNEL1_ID, 234);
    CHECK( _isAdcStarted );
    assertHasNoEvent();

    setMyAdcValue(567);
    assertHasAdcEventWithSample(CHANNEL1_ID, 567);
    CHECK( _isAdcStarted );
    assertHasNoEvent();
}





TEST(BasicAdcSource, oneEventTwoChannels) {

    AdcSourceChannel  sourceChannelData1;
    AdcSourceChannel *sourceChannel1 =
        AdcSourceChannel_init(&sourceChannelData1, CHANNEL1_ID);
    AdcSourceChannel  sourceChannelData2;
    AdcSourceChannel *sourceChannel2 =
        AdcSourceChannel_init(&sourceChannelData2, CHANNEL2_ID);

    AdcSource_addSourceChannel(_adcSource, sourceChannel1);
    AdcSource_addSourceChannel(_adcSource, sourceChannel2);
    assertHasNoEvent();

    setMyAdcValue(234);
    assertHasAdcEventWithSample(CHANNEL1_ID, 234);
    CHECK( _isAdcStarted );
    assertHasNoEvent();
}





TEST(BasicAdcSource, manyEventsTwoChannels) {

    AdcSourceChannel  sourceChannelData1;
    AdcSourceChannel *sourceChannel1 =
        AdcSourceChannel_init(&sourceChannelData1, CHANNEL1_ID);
    AdcSourceChannel  sourceChannelData2;
    AdcSourceChannel *sourceChannel2 =
        AdcSourceChannel_init(&sourceChannelData2, CHANNEL2_ID);

    AdcSource_addSourceChannel(_adcSource, sourceChannel1);
    AdcSource_addSourceChannel(_adcSource, sourceChannel2);
    assertHasNoEvent();

    setMyAdcValue(234);
    assertHasAdcEventWithSample(CHANNEL1_ID, 234);
    CHECK( _isAdcStarted );
    assertHasNoEvent();

    setMyAdcValue(432);
    assertHasAdcEventWithSample(CHANNEL2_ID, 432);
    CHECK( _isAdcStarted );
    assertHasNoEvent();

    setMyAdcValue(567);
    assertHasAdcEventWithSample(CHANNEL1_ID, 567);
    CHECK( _isAdcStarted );
    assertHasNoEvent();

    setMyAdcValue(765);
    assertHasAdcEventWithSample(CHANNEL2_ID, 765);
    CHECK( _isAdcStarted );
    assertHasNoEvent();
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

