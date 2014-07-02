/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/events/EventListener.h
 *
 * @brief Definition of the EventListener interface methods.
 *
 **************************************************************************/

#include <avrtk/events/EventListener.h>





/**********************************************************************//**
 *
 * @interface EventListener avrtk/events/EventListener.h <avrtk/events/EventListener.h>
 *
 * @brief A consumer of events.
 *
 **************************************************************************/





/**********************************************************************//**
 *
 * Consumes an event.
 *
 * @public @memberof EventListener
 * @pure
 *
 * @param self 
 *
 * @param event The Event being passed to this EventListener.
 *
 **************************************************************************/

void EventListener_notify(EventListener *self,
                          Event         *event) {

    self->vtable->notify(self, event);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

