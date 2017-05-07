/**************************************************************************
 *
 * Copyright (c) 2017 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/tasks/BasicAdc.h
 *
 * @brief Definition of the BasicAdcService class methods.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/adc/AdcEvent.h>
#include <avrtk/adc/AdcEventType.h>
#include <avrtk/adc/BasicAdcService.h>


/**
 * @class BasicAdcService avrtk/adc/BasicAdcService.h <avrtk/adc/BasicAdcService.h>
 * @implements AdcService
 * @ingroup avrtk_adc
 *
 * @brief A concrete implementation of the AdcService interface.
 */


static void BasicAdcService_onSample(
        BasicAdcService *self,
        AdcEvent *event);

static void BasicAdcService_start(AdcService  *self);

static AdcChannel *BasicAdcService_initChannel(
        AdcService *self,
        AdcChannel *channel,
        int channelId);

static AdcServiceInterface interface = {
    .start = BasicAdcService_start,
    .initChannel = BasicAdcService_initChannel,
};


static EventListener *AdcServiceAdcListener_asEventListener(
        AdcServiceAdcListener *self);

static void AdcServiceAdcListener_init(
        AdcServiceAdcListener *self,
        BasicAdcService *adcService);

static void AdcServiceAdcListener_onEvent(
        EventListener *self,
        Event *Event);

static EventListenerInterface adcServiceEventListenerInterface = {
    .onEvent = AdcServiceAdcListener_onEvent
};


/**
 *
 */
BasicAdcService *BasicAdcService_init(
        BasicAdcService *self,
        EventManager *eventManager,
        BasicAdcSource *adcSource) {

    self->base.vtable = &interface;
    self->eventManager = eventManager;
    self->adcSource = adcSource;
    self->channelListHead = NULL;
    AdcServiceAdcListener_init(&self->adcListener, self);

    return self;
}


/**
 *
 */
AdcService *BasicAdcService_asAdcService(BasicAdcService *self) {

    AdcService *result = (AdcService *)self;

    return result;
}


/**
 *
 */
static void BasicAdcService_start(AdcService  *baseSelf) {

    BasicAdcService *self = (BasicAdcService *)baseSelf;
    EventListener *adcListener =
        AdcServiceAdcListener_asEventListener(&self->adcListener);

    EventManager_addListener(
            self->eventManager,
            AdcEventType_get(),
            adcListener);
}


/**
 *
 */
static AdcChannel *BasicAdcService_initChannel(
        AdcService *baseSelf,
        AdcChannel *channel,
        int channelId) {

    BasicAdcService *self = (BasicAdcService *)baseSelf;
    AdcChannel_init(channel, channelId);

    channel->next = self->channelListHead;
    self->channelListHead = channel;

    BasicAdcSource_addSourceChannel(
            self->adcSource,
            AdcChannel_getSourceChannel(channel));

    return channel;
}


/**
 *
 */
static void BasicAdcService_onSample(
        BasicAdcService *self,
        AdcEvent *event) {

    AdcSample *sample          = AdcEvent_getSample(event);
    int        sampleChannelId = AdcSample_getChannelId(sample);

    for ( AdcChannel *channel = self->channelListHead;
          channel != NULL;
          channel = channel->next ) {

        int channelId = AdcChannel_getChannelId(channel);

        if ( channelId == sampleChannelId ) {
            AdcChannel_onSample(channel, sample);
        }
    }
}


/**
 *
 */
static void AdcServiceAdcListener_init(
        AdcServiceAdcListener *self,
        BasicAdcService *adcService) {

    self->base.vtable = &adcServiceEventListenerInterface;
    self->adcService  = adcService;
}


/**
 *
 */
static EventListener *AdcServiceAdcListener_asEventListener(
        AdcServiceAdcListener *self) {

    EventListener *result = (EventListener *)self;

    return result;
}


/**
 *
 */
static void AdcServiceAdcListener_onEvent(
        EventListener *baseSelf,
        Event *event) {

    AdcServiceAdcListener *self = (AdcServiceAdcListener *)baseSelf;
    AdcEvent *adcEvent = AdcEvent_fromEvent(event);

    BasicAdcService_onSample(self->adcService, adcEvent);
}
