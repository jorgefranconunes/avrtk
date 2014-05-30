/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef TESTEVENTSOURCE_H
#define TESTEVENTSOURCE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <avrtk/events/Event.h>
#include <avrtk/events/EventSource.h>





    struct TestEventSourceStruct {
        EventSource base;
        Event      *event;
        int        *tickCountList;
        int         tickCountSize;
        int         currentTick;
        int         currentRemaining;
        bool        isActive;
        int         queryCount;
    };
    typedef struct TestEventSourceStruct TestEventSource;

    TestEventSource *TestEventSource_init(TestEventSource *self,
                                          Event           *event,
                                          int             *tickCountList,
                                          int              tickCountSize);

    Event *TestEventSource_poll(EventSource *self);

    int TestEventSource_getQueryCount(TestEventSource *self);

    EventSource *TestEventSource_asEventSource(TestEventSource *self);





#ifdef __cplusplus
}
#endif

#endif

