/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/ticks/CounterTickSource.h>
#include <avrtk/ticks/TickEventType.h>





static EventSourceInterface interface = {
    .poll = CounterTickSource_poll
};





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

CounterTickSource *
CounterTickSource_init(CounterTickSource *self,
                       long             (*tickCountGetter)(void),
                       int                incrementFactorN,
                       int                incrementFactorD) {

    self->base.vtable     = &interface;
    self->tickCountGetter = tickCountGetter;
    self->lastTickCount   = 0;

    CounterClock_init(&self->clock, incrementFactorN, incrementFactorD);
    Event_init(&self->tickEvent, TickEventType_get());

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

Event *CounterTickSource_poll(EventSource *baseSelf) {

    CounterTickSource *self = (CounterTickSource *)baseSelf;

    Event *result           = NULL;
    long   currentTickCount = self->tickCountGetter();

    if ( currentTickCount != self->lastTickCount ) {
        self->lastTickCount = currentTickCount;
        CounterClock_update(&self->clock, currentTickCount);
        result = &self->tickEvent;
    }

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

Clock *CounterTickSource_getClock(CounterTickSource *self) {

    Clock *result = CounterClock_asClock(&self->clock);

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventSource *CounterTickSource_asEventSource(CounterTickSource *self) {

    EventSource *result = (EventSource *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

