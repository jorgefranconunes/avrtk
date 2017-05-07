/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <assert.h>
#include <stddef.h>

#include <avrtk/events/Event.h>
#include <avrtk/events/TestEventListener.h>


static void TestEventListener_onEvent(
        EventListener *baseSelf,
        Event *event);


static EventListenerInterface interface = {
    .onEvent  = TestEventListener_onEvent
};


/**
 *
 */
TestEventListener *TestEventListener_init(
        TestEventListener *self,
        EventType *eventType,
        int maxEventCount,
        EventManager *eventManager) {

    self->base.vtable   = &interface;
    self->eventType     = eventType;
    self->maxEventCount = maxEventCount;
    self->eventManager  = eventManager;
    self->eventCount    = 0;

    return self;
}


/**
 *
 */
static void TestEventListener_onEvent(
        EventListener *baseSelf,
        Event *event) {

    TestEventListener *self              = (TestEventListener *)baseSelf;
    EventType         *expectedEventType = self->eventType;

    if ( NULL != expectedEventType ) {
        assert( expectedEventType == Event_getEventType(event) );
    }

    if ( self->eventCount < self->maxEventCount ) {
        ++(self->eventCount);

        if ( self->eventCount == self->maxEventCount ) {
            EventManager_stop(self->eventManager);
        }
    }
}


/**
 *
 */
int TestEventListener_getEventCount(TestEventListener *self) {

    int result = self->eventCount;

    return result;
}


/**
 *
 */
EventListener *TestEventListener_asEventListener(TestEventListener *self) {

    EventListener *result = (EventListener *)self;

    return result;
}

