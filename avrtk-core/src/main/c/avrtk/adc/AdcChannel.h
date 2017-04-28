/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef ADCCHANNEL_H
#define ADCCHANNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcListener.h>
#include <avrtk/adc/AdcSourceChannel.h>


    typedef struct AdcChannelStruct AdcChannel;

    struct AdcChannelStruct {
        AdcSourceChannel sourceChannel;
        AdcListener *listenerListHead;
        AdcChannel *next;
    };

    AdcChannel *AdcChannel_init(
            AdcChannel *self,
            int channelId);

    int AdcChannel_getChannelId(AdcChannel *self);

    void AdcChannel_addListener(
            AdcChannel  *self,
            AdcListener *listener);

    void AdcChannel_onSample(
            AdcChannel *self,
            AdcSample  *sample);

    AdcSourceChannel *AdcChannel_getSourceChannel(AdcChannel *self);





#ifdef __cplusplus
}
#endif

#endif
