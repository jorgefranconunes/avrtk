/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/AdcEvent.h>
#include <avrtk/adc/AdcEventType.h>





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcEvent *AdcEvent_init(AdcEvent *self,
                        int       channelId,
                        uint16_t  value) {

    EventType *eventType = AdcEventType_get();

    Event_init(&self->base, eventType);
    AdcSample_init(&self->sample, channelId, value);

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcSample *AdcEvent_getSample(AdcEvent *self) {

    return &self->sample;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

Event *AdcEvent_asEvent(AdcEvent *self) {

    Event *result = (Event *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcEvent *AdcEvent_fromEvent(Event *baseSelf) {

    AdcEvent *result = (AdcEvent *)baseSelf;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

