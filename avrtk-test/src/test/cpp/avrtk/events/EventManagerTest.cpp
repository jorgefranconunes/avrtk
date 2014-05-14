/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <CppUTest/TestHarness.h>

#include <avrtk/events/Event.h>
#include <avrtk/events/EventManager.h>
#include <avrtk/events/EventSource.h>
#include <avrtk/events/EventType.h>

#include <avrtk/events/TestEventListener.h>
#include <avrtk/events/TestEventSource.h>





static EventType  evType1Data;
static EventType *evType1 = EventType_init(&evType1Data);
static EventType  evType2Data;
static EventType *evType2 = EventType_init(&evType2Data);

static Event  ev1Data;
static Event *ev1 = Event_init(&ev1Data, evType1);
static Event  ev2Data;
static Event *ev2 = Event_init(&ev2Data, evType2);





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TEST_GROUP(EventManagerBasics) {


    EventManager eventManager;


    void setup() {

        EventManager_init(&eventManager);
    }


    void teardown() {
    }





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

    void testMultiEvents(int             sourceCount,
                         TestEventSource sourceList[],
                         Event          *sourceEventList[],
                         int            *tickCountListList[],
                         int             tickCountSizeList[],
                         int             expectedQueryCount,

                         int               listenerCount,
                         TestEventListener listenerList[],
                         EventType        *listenerEventTypeList[],
                         int               maxEventCountList[],
                         int               expectedEventCount[]) {

        for ( int i=0; i<sourceCount; ++i ) {
            TestEventSource *rSource = &sourceList[i];
            TestEventSource_init(rSource,
                                 sourceEventList[i],
                                 tickCountListList[i],
                                 tickCountSizeList[i]);
            EventManager_addSource(&eventManager,
                                   TestEventSource_asEventSource(rSource));
        }

        for ( int i=0; i<listenerCount; ++i ) {
            TestEventListener *rLstnr = &listenerList[i];
            TestEventListener_init(rLstnr,
                                   listenerEventTypeList[i],
                                   maxEventCountList[i],
                                   &eventManager);
            EventManager_addListener(&eventManager,
                                     listenerEventTypeList[i],
                                     TestEventListener_asEventListener(rLstnr));
        }

        EventManager_start(&eventManager);

        for ( int i=0; i<sourceCount; ++i ) {
            TestEventSource *rSource = &sourceList[i];
            CHECK_EQUAL(expectedQueryCount,
                        TestEventSource_getQueryCount(rSource));
        }

        for ( int i=0; i<listenerCount; ++i ) {
            TestEventListener *rLstnr = &listenerList[i];
            CHECK_EQUAL(expectedEventCount[i],
                        TestEventListener_getEventCount(rLstnr));
        }
    }





/**************************************************************************
 *
 * Test one source with one listener.
 *
 **************************************************************************/

    void test1x1(int tickCountList[],
                 int tickCountSize,
                 int maxEventCount,
                 int expectedQueryCount,
                 int expectedEventCount) {

        Event     *eventList[]     = { ev1 };
        EventType *eventTypeList[] = { evType1 };

        TestEventSource sourceList[1];
        int            *tickCountListList[] = { tickCountList };
        int             tickCountSizeList[] = { tickCountSize };

        TestEventListener listenerList[1];
        int               maxEventCountList[] = { maxEventCount };
        int               expectedEventCountList[] = { expectedEventCount };

        testMultiEvents(1,
                        sourceList,
                        eventList,
                        tickCountListList,
                        tickCountSizeList,
                        expectedQueryCount,
                        1,
                        listenerList,
                        eventTypeList,
                        maxEventCountList,
                        expectedEventCountList);
    }





/**************************************************************************
 *
 * Test two sources with one listener.
 *
 **************************************************************************/

    void test2x1(Event     *sourceEventList[],
                 int       *tickCountListList[],
                 int        tickCountSizeList[],
                 int        expectedQueryCount,
                 EventType *listenerEventType,
                 int        maxEventCount,
                 int        expectedEventCount) {

        TestEventSource sourceList[2];

        TestEventListener listenerList[1];
        EventType        *listenerEventTypeList[] = { listenerEventType };
        int               maxEventCountList[] = { maxEventCount };
        int               expectedEventCountList[] = { expectedEventCount };

        testMultiEvents(2,
                        sourceList,
                        sourceEventList,
                        tickCountListList,
                        tickCountSizeList,
                        expectedQueryCount,
                        1,
                        listenerList,
                        listenerEventTypeList,
                        maxEventCountList,
                        expectedEventCountList);
    }


};





TEST(EventManagerBasics, doInit) {

    // Everything is handled in the testsuit setup.
}





TEST(EventManagerBasics, startWithNothingToDo) {

    EventManager_start(&eventManager);
}





TEST(EventManagerBasics, startWithNoListener) {

    TestEventSource source;

    TestEventSource_init(&source, ev1, NULL, 0);

    EventManager_addSource(&eventManager,
                           TestEventSource_asEventSource(&source));
    EventManager_start(&eventManager);

    CHECK_EQUAL(0, TestEventSource_getQueryCount(&source));
}





TEST(EventManagerBasics, startWithNoSource) {

    TestEventListener listener;

    TestEventListener_init(&listener, evType1, 1, &eventManager);

    EventManager_addListener(&eventManager,
                             evType1,
                             TestEventListener_asEventListener(&listener));
    EventManager_start(&eventManager);

    CHECK_EQUAL(0, TestEventListener_getEventCount(&listener));
}





TEST(EventManagerBasics, oneEvent) {

    int tickCountList[] = { 1 };

    test1x1(tickCountList, 1, 1, 1, 1);
}





TEST(EventManagerBasics, multipleEvents01) {

    int tickCountList[] = { 10, 0 };
    test1x1(tickCountList, 2, 10, 10, 10);
}





TEST(EventManagerBasics, multipleEvents02) {

    int tickCountList[] = { 10, 0, 10 };
    test1x1(tickCountList, 3, 15, 15, 15);
}





TEST(EventManagerBasics, multipleEvents03) {

    int tickCountList[] = { 10, 4, 10 };
    test1x1(tickCountList, 3, 15, 19, 15);
}





TEST(EventManagerBasics, multipleEvents04) {

    int tickCountList[] = { 0, 10, 4, 10 };
    test1x1(tickCountList, 4, 3, 13, 3);
}





TEST(EventManagerBasics, twoSources01) {

    Event     *sourceEventList[] = { ev1, ev2 };
    int        tickCountList01[] = { 2, 3 };
    int        tickCountList02[] = { 4, 5 };
    int       *tickCountListList[] = { tickCountList01, tickCountList02 };
    int        tickCountSizeList[] = { 2, 2 };
    int        expectedQueryCount = 3;
    EventType *listenerEventType  = evType2;
    int        maxEventCount      = 3;
    int        expectedEventCount = 3;

    test2x1(sourceEventList,
            tickCountListList,
            tickCountSizeList,
            expectedQueryCount,
            listenerEventType,
            maxEventCount,
            expectedEventCount);
}





TEST(EventManagerBasics, twoSources02) {

    Event     *sourceEventList[] = { ev1, ev1 };
    int        tickCountList01[] = { 2, 3 };
    int        tickCountList02[] = { 4, 5 };
    int       *tickCountListList[] = { tickCountList01, tickCountList02 };
    int        tickCountSizeList[] = { 2, 2 };
    int        expectedQueryCount = 3;
    EventType *listenerEventType  = evType1;
    int        maxEventCount      = 5;
    int        expectedEventCount = 5;

    test2x1(sourceEventList,
            tickCountListList,
            tickCountSizeList,
            expectedQueryCount,
            listenerEventType,
            maxEventCount,
            expectedEventCount);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

