/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/adc/AdcChannel.h>

#include <avrtk/adc/TestAdcListener.h>





const int CHANNEL1_ID = 17;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(AdcChannel) {


    AdcChannel  _channelData;
    AdcChannel *_channel;


    void setup() {

        _channel = AdcChannel_init(&_channelData, CHANNEL1_ID);
    }


    void teardown() {
    }





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

    void testListeners(TestAdcListener listenerList[],
                       int             listenerCount,
                       int             sampleList[],
                       int             sampleCount) {

        for ( int i=0; i<listenerCount; ++i ) {
            TestAdcListener *testListener =
                TestAdcListener_init(&listenerList[i]);
            AdcListener     *listener =
                TestAdcListener_asAdcListener(testListener);
            AdcChannel_addListener(_channel, listener);
        }

        for ( int i=0; i<sampleCount; ++i ) {
            int        value  = sampleList[i];
            AdcSample  sampleData;
            AdcSample *sample =
                AdcSample_init(&sampleData, CHANNEL1_ID, value);

            for ( int j=0; j<listenerCount; ++j ) {
                TestAdcListener *testListener = &listenerList[j];

                CHECK_EQUAL( i, TestAdcListener_getNotifyCount(testListener) );
            }

            AdcChannel_notify(_channel, sample);

            for ( int j=0; j<listenerCount; ++j ) {
                TestAdcListener *testListener = &listenerList[j];

                CHECK_EQUAL( i+1,
                             TestAdcListener_getNotifyCount(testListener) );

                AdcSample *lSample =
                    TestAdcListener_getSample(testListener);
                CHECK_EQUAL( CHANNEL1_ID, AdcSample_getChannelId(lSample) );
                CHECK_EQUAL( value, AdcSample_getValue(lSample) );
            }

            for ( int j=0; j<listenerCount; ++j ) {
                TestAdcListener *testListener = &listenerList[j];

                CHECK_EQUAL( i+1,
                             TestAdcListener_getNotifyCount(testListener) );

                AdcSample *lSample =
                    TestAdcListener_getSample(testListener);
                CHECK_EQUAL( CHANNEL1_ID, AdcSample_getChannelId(lSample) );
                CHECK_EQUAL( value, AdcSample_getValue(lSample) );
            }
        }

        for ( int i=0; i<listenerCount; ++i ) {
            CHECK_EQUAL( sampleCount,
                         TestAdcListener_getNotifyCount(&listenerList[i]) );
        }
    }


};





TEST(AdcChannel, getChannelId) {

    CHECK_EQUAL( CHANNEL1_ID, AdcChannel_getChannelId(_channel) );
}





TEST(AdcChannel, getSourceChannel) {

    AdcSourceChannel *sourceChannel = AdcChannel_getSourceChannel(_channel);

    CHECK_EQUAL( CHANNEL1_ID, AdcSourceChannel_getChannelId(sourceChannel) );
}





TEST(AdcChannel, notifyWithNoListeners) {

    AdcSample  sampleData;
    AdcSample *sample = AdcSample_init(&sampleData, CHANNEL1_ID, 123);

    AdcChannel_notify(_channel, sample);

    // Nothing is supposed to happen, actually...
}





TEST(AdcChannel, notifyWithOneListener) {

    TestAdcListener  testListenerData;
    TestAdcListener *testListener = TestAdcListener_init(&testListenerData);
    AdcListener     *listener     =TestAdcListener_asAdcListener(testListener);
    AdcSample        sampleData;
    AdcSample       *sample = AdcSample_init(&sampleData, CHANNEL1_ID, 123);

    AdcChannel_addListener(_channel, listener);
    CHECK_EQUAL( 0, TestAdcListener_getNotifyCount(testListener) );

    AdcChannel_notify(_channel, sample);
    CHECK_EQUAL( 1, TestAdcListener_getNotifyCount(testListener) );

    AdcSample *lSample = TestAdcListener_getSample(testListener);
    CHECK_EQUAL( CHANNEL1_ID, AdcSample_getChannelId(lSample) );
    CHECK_EQUAL( 123, AdcSample_getValue(lSample) );
}





TEST(AdcChannel, notifyWithOneListenerAgain) {

    TestAdcListener listenerList[1];
    int             listenerCount = 1;

    int sampleList[] = { 123 };
    int sampleCount  = 1;

    testListeners(listenerList, listenerCount, sampleList, sampleCount);
}





TEST(AdcChannel, notifyWithManyListeners) {

    TestAdcListener listenerList[7];
    int             listenerCount = 7;

    int sampleList[] = { 123, 456, 789, 76, 27, 19, 21 };
    int sampleCount  = 7;

    testListeners(listenerList, listenerCount, sampleList, sampleCount);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

