/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/adc/BasicAdcService.h>
#include <avrtk/adc/BasicAdcSource.h>
#include <avrtk/adc/TestAdcListener.h>


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




/**
 *
 */
static bool startMyAdc(int channel) {

    CHECK ( !_isAdcStarted || _isAdcCompleted);

    _isAdcStarted   = true;
    _isAdcCompleted = false;
    _adcValue       = 0;

    return true;
}


/**
 *
 */
static bool isMyAdcCompleted() {

    CHECK ( _isAdcStarted || _isAdcCompleted);

    return _isAdcCompleted;
}


/**
 *
 */
static uint16_t getMyLatestAdcValue(void) {

    CHECK ( _isAdcCompleted );

    return _adcValue;
}


/**
 *
 */
static void resetMyAdc() {

    _isAdcStarted   = false;
    _isAdcCompleted = false;
    _adcValue       = 0;
}


/**
 *
 */
static void setMyAdcValue(uint16_t adcValue) {

    _isAdcStarted   = false;
    _isAdcCompleted = true;
    _adcValue       = adcValue;
}


/**
 *
 */
TEST_GROUP(BasicAdcService) {


    EventManager _eventManagerData;
    EventManager *_eventManager;
    BasicAdcSource _basicAdcSourceData;
    BasicAdcService _adcServiceData;
    AdcService *_adcService;


    /**
     *
     */
    void setup() {

        resetMyAdc();

        EventManager *eventManager = EventManager_init(&_eventManagerData);

        BasicAdcSource *adcSource = BasicAdcSource_init(
                    &_basicAdcSourceData,
                    &startMyAdc,
                    &isMyAdcCompleted,
                    &getMyLatestAdcValue);

        EventManager_addSource(
                eventManager,
                BasicAdcSource_asEventSource(adcSource));

        BasicAdcService *basicAdcService = BasicAdcService_init(
                &_adcServiceData,
                eventManager,
                adcSource);
        AdcService *adcService = BasicAdcService_asAdcService(basicAdcService);
        AdcService_start(adcService);

        _eventManager = eventManager;
        _adcService   = adcService;
    }


    /**
     *
     */
    void teardown() {
        // Nothing to do...
    }


    /**
     *
     */
    void checkSample(
            int expectedChannelId,
            uint16_t expectedValue,
            AdcSample *actualSample) {

        CHECK_EQUAL( expectedChannelId, AdcSample_getChannelId(actualSample) );
        CHECK_EQUAL( expectedValue, AdcSample_getValue(actualSample) );
    }


};


/**
 *
 */
TEST(BasicAdcService, noEvents) {

    EventManager_sweep(_eventManager);
}


/**
 *
 */
TEST(BasicAdcService, noEventWithOneChannel) {

    TestAdcListener  adcListenerData;
    TestAdcListener *adcListener = TestAdcListener_init(&adcListenerData);
    AdcChannel  adcChannelData;
    AdcChannel *adcChannel =
        AdcService_initChannel(_adcService, &adcChannelData, CHANNEL1_ID);

    AdcChannel_addListener(adcChannel,
                           TestAdcListener_asAdcListener(adcListener));
    CHECK_EQUAL( 0, TestAdcListener_getNotifyCount(adcListener));

    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 0, TestAdcListener_getNotifyCount(adcListener));
}


/**
 *
 */
TEST(BasicAdcService, noEventWithOneChannelTwice) {

    TestAdcListener  adcListenerData;
    TestAdcListener *adcListener = TestAdcListener_init(&adcListenerData);
    AdcChannel  adcChannelData;
    AdcChannel *adcChannel =
        AdcService_initChannel(_adcService, &adcChannelData, CHANNEL1_ID);

    AdcChannel_addListener(adcChannel,
                           TestAdcListener_asAdcListener(adcListener));
    CHECK_EQUAL( 0, TestAdcListener_getNotifyCount(adcListener));

    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 0, TestAdcListener_getNotifyCount(adcListener));

    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 0, TestAdcListener_getNotifyCount(adcListener));
}


/**
 *
 */
TEST(BasicAdcService, oneEventOneChannel) {

    TestAdcListener  adcListenerData;
    TestAdcListener *adcListener = TestAdcListener_init(&adcListenerData);
    AdcChannel  adcChannelData;
    AdcChannel *adcChannel =
        AdcService_initChannel(_adcService, &adcChannelData, CHANNEL1_ID);

    AdcChannel_addListener(adcChannel,
                           TestAdcListener_asAdcListener(adcListener));
    CHECK_EQUAL( 0, TestAdcListener_getNotifyCount(adcListener));

    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 0, TestAdcListener_getNotifyCount(adcListener));

    setMyAdcValue(456);
    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 1, TestAdcListener_getNotifyCount(adcListener));
    checkSample( CHANNEL1_ID, 456, TestAdcListener_getSample(adcListener));

    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 1, TestAdcListener_getNotifyCount(adcListener));
}


/**
 *
 */
TEST(BasicAdcService, twoEventsOneChannel) {

    TestAdcListener  adcListenerData;
    TestAdcListener *adcListener = TestAdcListener_init(&adcListenerData);
    AdcChannel  adcChannelData;
    AdcChannel *adcChannel =
        AdcService_initChannel(_adcService, &adcChannelData, CHANNEL1_ID);

    AdcChannel_addListener(adcChannel,
                           TestAdcListener_asAdcListener(adcListener));

    setMyAdcValue(456);
    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 1, TestAdcListener_getNotifyCount(adcListener));
    checkSample( CHANNEL1_ID, 456, TestAdcListener_getSample(adcListener));

    setMyAdcValue(789);
    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 2, TestAdcListener_getNotifyCount(adcListener));
    checkSample( CHANNEL1_ID, 789, TestAdcListener_getSample(adcListener));

    EventManager_sweep(_eventManager);
    CHECK_EQUAL( 2, TestAdcListener_getNotifyCount(adcListener));
}


// TEST(BasicAdcService, oneEventTwoChannels) {

//     AdcSourceChannel  sourceChannelData1;
//     AdcSourceChannel *sourceChannel1 =
//         AdcSourceChannel_init(&sourceChannelData1, CHANNEL1_ID);
//     AdcSourceChannel  sourceChannelData2;
//     AdcSourceChannel *sourceChannel2 =
//         AdcSourceChannel_init(&sourceChannelData2, CHANNEL2_ID);

//     AdcSource_addSourceChannel(_adcSource, sourceChannel1);
//     AdcSource_addSourceChannel(_adcSource, sourceChannel2);
//     assertHasNoEvent();

//     setMyAdcValue(234);
//     assertHasAdcEventWithSample(CHANNEL1_ID, 234);
//     CHECK( _isAdcStarted );
//     assertHasNoEvent();
// }


// TEST(BasicAdcService, manyEventsTwoChannels) {

//     AdcSourceChannel  sourceChannelData1;
//     AdcSourceChannel *sourceChannel1 =
//         AdcSourceChannel_init(&sourceChannelData1, CHANNEL1_ID);
//     AdcSourceChannel  sourceChannelData2;
//     AdcSourceChannel *sourceChannel2 =
//         AdcSourceChannel_init(&sourceChannelData2, CHANNEL2_ID);

//     AdcSource_addSourceChannel(_adcSource, sourceChannel1);
//     AdcSource_addSourceChannel(_adcSource, sourceChannel2);
//     assertHasNoEvent();

//     setMyAdcValue(234);
//     assertHasAdcEventWithSample(CHANNEL1_ID, 234);
//     CHECK( _isAdcStarted );
//     assertHasNoEvent();

//     setMyAdcValue(432);
//     assertHasAdcEventWithSample(CHANNEL2_ID, 432);
//     CHECK( _isAdcStarted );
//     assertHasNoEvent();

//     setMyAdcValue(567);
//     assertHasAdcEventWithSample(CHANNEL1_ID, 567);
//     CHECK( _isAdcStarted );
//     assertHasNoEvent();

//     setMyAdcValue(765);
//     assertHasAdcEventWithSample(CHANNEL2_ID, 765);
//     CHECK( _isAdcStarted );
//     assertHasNoEvent();
// }

