/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/events/EventType.h
 *
 * @brief Definition of the EventType class methods.
 *
 **************************************************************************/

#include <avrtk/events/EventType.h>





/**********************************************************************//**
 *
 * @class EventType avrtk/events/EventType.h <avrtk/events/EventType.h>
 *
 * @brief The type of an event.
 *
 * An event type is characterized by a unique integer ID. The ID is
 * automatically assigned when an EventType is created.
 *
 * In practice, the ID of the event type is rarely used. An event
 * event type corresponds directly to an EventType
 * instance. Therefore, to check if two event types are the same you
 * can just check if those two EventType objects are the same object
 * by comparing references (i. e. pointers).
 *
 **************************************************************************/





static int _eventIdCounter = 0;





/**********************************************************************//**
 *
 * Initializes an EventType object.
 *
 * The ID for the new EventType instance is automatically assigned.
 *
 * @public @memberof EventType
 *
 * @param self Reference to the EventType object to be initialized.
 *
 **************************************************************************/

EventType *EventType_init(EventType *self) {

    int id = ++_eventIdCounter;

    self->id = id;

    return self;
}





/**********************************************************************//**
 *
 * Retrieves the ID of the EventType.
 *
 * @public @memberof EventType
 *
 * @param self
 *
 * @return The ID of this event type.
 *
 **************************************************************************/

int EventType_getId(EventType *self) {

    return self->id;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

