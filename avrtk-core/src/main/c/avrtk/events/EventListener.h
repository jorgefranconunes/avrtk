/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/Event.h>





    typedef struct EventListenerStruct EventListener;

    typedef struct EventListenerInterfaceStruct EventListenerInterface;
    struct EventListenerInterfaceStruct {
        void (*onEvent)(EventListener*, Event*);
    };

    struct EventListenerStruct {
        EventListenerInterface *vtable;
        EventType              *eventType;
        EventListener          *next;
    };

    void EventListener_onEvent(
            EventListener *self,
            Event *event);





#ifdef __cplusplus
}
#endif

#endif
