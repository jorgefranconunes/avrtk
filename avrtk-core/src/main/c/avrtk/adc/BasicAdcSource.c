/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/adc/BasicAdcSource.h>


static Event *BasicAdcSource_poll(EventSource *baseSelf);

static void BasicAdcSource_startAdcForChannel(
        BasicAdcSource   *self,
        AdcSourceChannel *channel);


static EventSourceInterface eventSourceInterface = {
    .poll = &BasicAdcSource_poll
};


/**
 *
 */
BasicAdcSource *BasicAdcSource_init(
        BasicAdcSource *self,
        bool (*startAdc)(int),
        bool (*isAdcCompleted)(void),
        uint16_t (*getLatestAdcValue)(void)) {

    self->base.vtable = &eventSourceInterface;

    self->channelListHead = NULL;
    self->currentChannel = NULL;
    self->startAdc = startAdc;
    self->isAdcCompleted = isAdcCompleted;
    self->getLatestAdcValue = getLatestAdcValue;

    return self;
}


/**
 *
 */
EventSource *BasicAdcSource_asEventSource(BasicAdcSource *self) {

    EventSource *result = (EventSource *)self;

    return result;
}


/**
 *
 */
void BasicAdcSource_addSourceChannel(
        BasicAdcSource *self,
        AdcSourceChannel *channel) {

    bool isFirstTime = (self->channelListHead == NULL);

    channel->next = self->channelListHead;
    self->channelListHead = channel;

    if ( isFirstTime ) {
        BasicAdcSource_startAdcForChannel(self, NULL);
    }
}


/**
 *
 */
static Event *BasicAdcSource_poll(EventSource *baseSelf) {

    BasicAdcSource *self = (BasicAdcSource *)baseSelf;
    AdcSourceChannel *currentChannel = self->currentChannel;
    Event *result = NULL;

    if ( currentChannel != NULL ) {
        if ( self->isAdcCompleted() ) {
            int channelId =
                    AdcSourceChannel_getChannelId(currentChannel);
            uint16_t value =
                    self->getLatestAdcValue();
            AdcEvent *adcEvent =
                    AdcEvent_init(&self->eventData, channelId, value);

            result = AdcEvent_asEvent(adcEvent);

            BasicAdcSource_startAdcForChannel(self, currentChannel->next);
        } else {
            // The conversion is still progressing. We will not
            // generate an event.
        }
    } else {
        // We have no registered ADC sources. That means we do not
        // need to check for conversions.
    }

    return result;
}


/**
 *
 */
static void BasicAdcSource_startAdcForChannel(
        BasicAdcSource   *self,
        AdcSourceChannel *channel) {

    if ( channel == NULL ) {
        channel = self->channelListHead;
    }

    if ( channel != NULL ) {
        int channelId = AdcSourceChannel_getChannelId(channel);

        self->currentChannel = channel;
        self->startAdc(channelId);
    }
}

