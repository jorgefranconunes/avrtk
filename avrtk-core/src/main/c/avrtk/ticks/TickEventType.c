/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/ticks/TickEventType.h>





static EventType  _tickEventTypeData;
static EventType *_tickEventType = NULL;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventType *TickEventType_get() {

    if ( NULL == _tickEventType ) {
        EventType_init(&_tickEventTypeData);

        _tickEventType = &_tickEventTypeData;
    }

    return _tickEventType;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/


