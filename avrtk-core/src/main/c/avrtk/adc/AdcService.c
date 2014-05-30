/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/adc/AdcEvent.h>
#include <avrtk/adc/AdcEventType.h>
#include <avrtk/adc/AdcService.h>





static EventListener *
AdcServiceAdcListener_asEventListener(AdcServiceAdcListener *self);

static void
AdcServiceAdcListener_init(AdcServiceAdcListener *self,
                             AdcService          *adcService);

static void
AdcServiceAdcListener_notify(EventListener *self,
                               Event         *Event);

static EventListenerInterface adcServiceEventListenerInterface = {
    .notify = AdcServiceAdcListener_notify
};





static void AdcService_adcEvent(AdcService *self,
                                AdcEvent   *event);





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcService *AdcService_init(AdcService  *self,
                            EventManager *eventManager,
                            AdcSource    *adcSource) {

    self->eventManager    = eventManager;
    self->adcSource       = adcSource;
    self->channelListHead = NULL;
    AdcServiceAdcListener_init(&self->adcListener, self);

    return self;
}






/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void AdcService_start(AdcService  *self) {

    EventListener *adcListener =
        AdcServiceAdcListener_asEventListener(&self->adcListener);

    EventManager_addListener(self->eventManager,
                             AdcEventType_get(),
                             adcListener);
}






/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcChannel *AdcService_initChannel(AdcService  *self,
                                   AdcChannel  *channel,
                                   int          channelId) {

    AdcChannel_init(channel, channelId);

    channel->next         = self->channelListHead;
    self->channelListHead = channel;

    AdcSource_addSourceChannel(self->adcSource,
                               AdcChannel_getSourceChannel(channel));

    return channel;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void AdcService_adcEvent(AdcService *self,
                                AdcEvent   *event) {

    AdcSample *sample          = AdcEvent_getSample(event);
    int        sampleChannelId = AdcSample_getChannelId(sample);

    for ( AdcChannel *channel = self->channelListHead;
          channel != NULL;
          channel = channel->next ) {

        int channelId = AdcChannel_getChannelId(channel);

        if ( channelId == sampleChannelId ) {
            AdcChannel_notify(channel, sample);
        }
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void
AdcServiceAdcListener_init(AdcServiceAdcListener *self,
                           AdcService            *adcService) {

    self->base.vtable = &adcServiceEventListenerInterface;
    self->adcService  = adcService;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventListener *
AdcServiceAdcListener_asEventListener(AdcServiceAdcListener *self) {

    EventListener *result = (EventListener *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void AdcServiceAdcListener_notify(EventListener *baseSelf,
                                         Event         *event) {

    AdcServiceAdcListener *self = (AdcServiceAdcListener *)baseSelf;
    AdcEvent              *adcEvent = AdcEvent_fromEvent(event);

    AdcService_adcEvent(self->adcService, adcEvent);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

