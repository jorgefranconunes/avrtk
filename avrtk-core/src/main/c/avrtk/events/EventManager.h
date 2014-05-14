/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/EventListener.h>
#include <avrtk/events/EventType.h>
#include <avrtk/events/EventSource.h>





    typedef enum EventManagerStatus {
        STOPED,
        STARTED
    } EventManagerStatus;


    typedef struct EventManagerStruct EventManager;
    struct EventManagerStruct {
        EventManagerStatus status;
        EventSource       *eventSourceListHead;
        EventListener     *eventListenerListHead;
    };


    EventManager *EventManager_init(EventManager *self);

    void EventManager_addSource(EventManager    *self,
                                EventSource     *eventSource);

    void EventManager_addListener(EventManager  *self,
                                  EventType     *eventType,
                                  EventListener *eventListener);

    void EventManager_start(EventManager *self);

    void EventManager_stop(EventManager *self);

    void EventManager_sweep(EventManager *self);





#ifdef __cplusplus
}
#endif

#endif
