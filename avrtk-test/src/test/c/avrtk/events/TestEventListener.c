/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <assert.h>
#include <stddef.h>

#include <avrtk/events/Event.h>
#include <avrtk/events/TestEventListener.h>





static void TestEventListener_notify(EventListener *self,
                                     Event         *event);

static EventListenerInterface interface = {
    .notify  = TestEventListener_notify
};





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TestEventListener *TestEventListener_init(TestEventListener *self,
                                          EventType         *eventType,
                                          int                maxEventCount,
                                          EventManager      *eventManager) {

    self->base.vtable   = &interface;
    self->eventType     = eventType;
    self->maxEventCount = maxEventCount;
    self->eventManager  = eventManager;
    self->eventCount    = 0;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventListener *TestEventListener_asEventListener(TestEventListener *self) {

    EventListener *result = (EventListener *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int TestEventListener_getEventCount(TestEventListener *self) {

    int result = self->eventCount;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void TestEventListener_notify(EventListener *baseSelf,
                                     Event         *event) {

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





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

