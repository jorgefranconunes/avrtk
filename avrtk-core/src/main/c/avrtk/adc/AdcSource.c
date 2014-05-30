/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/AdcSource.h>





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void AdcSource_addSourceChannel(AdcSource        *self,
                                AdcSourceChannel *channel) {

    self->vtable->addSourceChannel(self, channel);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventSource *AdcSource_asEventSource(AdcSource *self) {

    EventSource *result = (EventSource *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

