/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/adc/AdcChannel.h>





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcChannel *AdcChannel_init(AdcChannel *self,
                            int         channelId) {

    AdcSourceChannel_init(&self->sourceChannel, channelId);
    self->listenerListHead = NULL;
    self->next             = NULL;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int AdcChannel_getChannelId(AdcChannel *self) {

    int result = AdcSourceChannel_getChannelId(&self->sourceChannel);

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void AdcChannel_addListener(AdcChannel  *self,
                            AdcListener *listener) {

    listener->next = self->listenerListHead;

    self->listenerListHead = listener;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void AdcChannel_notify(AdcChannel *self,
                       AdcSample  *sample) {

    for ( AdcListener *listener = self->listenerListHead;
          listener != NULL;
          listener = listener->next ) {
        AdcListener_notify(listener, sample);
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcSourceChannel *AdcChannel_getSourceChannel(AdcChannel *self) {

    AdcSourceChannel *result = &self->sourceChannel;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

