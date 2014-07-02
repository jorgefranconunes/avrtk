/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include <avrtk/events/Event.h>
#include <avrtk/events/EventManager.h>





static void EventManager_checkEventSources(EventManager *self);

static void EventManager_doEventLoop(EventManager *self);

static void EventManager_fireEvent(EventManager *self,
                                   Event        *event);

static bool EventManager_isRunning(EventManager *self);





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventManager *EventManager_init(EventManager *self) {

    self->status                = STOPED;
    self->eventSourceListHead   = NULL;
    self->eventListenerListHead = NULL;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void EventManager_addSource(EventManager    *self,
                            EventSource     *eventSource) {

    eventSource->next         = self->eventSourceListHead;
    self->eventSourceListHead = eventSource;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void EventManager_addListener(EventManager  *self,
                              EventType     *eventType,
                              EventListener *eventListener) {

    eventListener->eventType = eventType;
    eventListener->next      = self->eventListenerListHead;

    self->eventListenerListHead = eventListener;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void EventManager_start(EventManager *self) {

    if ( !EventManager_isRunning(self) ) {
        bool hasStuffToDo =
            (self->eventSourceListHead!=NULL)
            && (self->eventListenerListHead!=NULL);

        if ( hasStuffToDo ) {
            self->status = STARTED;
            EventManager_doEventLoop(self);
        } else {
            /* Either we have no event sources or we have no one to
               send events to. So we have nothing to do. */
        }
    } else {
        /* We are already running. We should blow up... */
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void EventManager_stop(EventManager *self) {

    self->status = STOPED;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void EventManager_sweep(EventManager *self) {

    EventManager_checkEventSources(self);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static bool EventManager_isRunning(EventManager *self) {

    bool isRunning = (self->status == STARTED);

    return isRunning;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void EventManager_doEventLoop(EventManager *self) {

    while ( EventManager_isRunning(self) ) {
        EventManager_checkEventSources(self);
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void EventManager_checkEventSources(EventManager *self) {

    
    for ( EventSource *eventSource = self->eventSourceListHead;
          eventSource != NULL;
          eventSource = eventSource->next ) {

        Event *event = EventSource_poll(eventSource);

        if ( NULL != event ) {
            EventManager_fireEvent(self, event);
        }
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void EventManager_fireEvent(EventManager *self,
                                   Event        *event) {

    EventType *eventType = Event_getEventType(event);

    for ( EventListener *listener = self->eventListenerListHead;
          listener != NULL;
          listener = listener->next ) {

        EventType *listenerType = listener->eventType;
        bool       isInterested = (eventType==listenerType);

        if ( isInterested ) {
            EventListener_notify(listener, event);
        }
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

