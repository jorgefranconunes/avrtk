/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/events/EventSource.h
 *
 * @brief Definition of the EventSource interface methods.
 *
 **************************************************************************/

#include <avrtk/events/EventSource.h>





/**********************************************************************//**
 *
 * @interface EventSource avrtk/events/EventSource.h <avrtk/events/EventSource.h>
 * @ingroup avrtk_events
 *
 * @brief A producer of events.
 *
 **************************************************************************/





/**********************************************************************//**
 *
 * Checks if an event is ready.
 *
 * @public @memberof EventSource
 * @pure
 *
 * If an event is ready then this method will return it. Otherwise it
 * will return a null reference. Each time an Event object is returned
 * (i.e. a non-null reference is returned) it means a new event has
 * just been generated.
 *
 * @param self
 *
 * @return An Event object, if an event was ready. NULL, if no event
 * was ready.
 *
 **************************************************************************/

Event *EventSource_poll(EventSource *self) {

    return self->vtable->poll(self);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

