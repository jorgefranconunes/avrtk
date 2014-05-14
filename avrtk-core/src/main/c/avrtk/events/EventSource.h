/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef EVENTSOURCE_H
#define EVENTSOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/events/Event.h>





    typedef struct EventSourceStruct EventSource;

    typedef struct EventSourceInterfaceStruct EventSourceInterface;
    struct EventSourceInterfaceStruct {
        Event *(*poll)(EventSource *);
    };

    struct EventSourceStruct {
        EventSourceInterface *vtable;
        EventSource          *next;
    };

    Event *EventSource_poll(EventSource *self);





#ifdef __cplusplus
}
#endif

#endif
