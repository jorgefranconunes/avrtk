/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef TESTEVENTLISTENER_H
#define TESTEVENTLISTENER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/EventListener.h>
#include <avrtk/events/EventManager.h>
#include <avrtk/events/EventType.h>





    struct TestEventListenerStruct {
        EventListener base;
        EventType    *eventType;
        int           maxEventCount;
        EventManager *eventManager;
        int           eventCount;
    };
    typedef struct TestEventListenerStruct TestEventListener;

    TestEventListener *TestEventListener_init(TestEventListener *self,
                                              EventType         *eventType,
                                              int                maxEventCount,
                                              EventManager      *eventManager);

    void TestEventListener_notify(EventListener *self,
                                  Event         *event);

    int TestEventListener_getEventCount(TestEventListener *self);

    EventListener *TestEventListener_asEventListener(TestEventListener *self);





#ifdef __cplusplus
}
#endif

#endif

