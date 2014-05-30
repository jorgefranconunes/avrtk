/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/adc/AdcEventType.h>





static EventType  _adcEventTypeData;
static EventType *_adcEventType = NULL;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventType *AdcEventType_get() {

    if ( NULL == _adcEventType ) {
        _adcEventType = EventType_init(&_adcEventTypeData);
    }

    return _adcEventType;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/


