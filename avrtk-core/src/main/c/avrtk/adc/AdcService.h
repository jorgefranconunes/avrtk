/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef ADCSERVICE_H
#define ADCSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcChannel.h>
#include <avrtk/adc/AdcSource.h>
#include <avrtk/events/EventListener.h>
#include <avrtk/events/EventManager.h>




    typedef struct AdcServiceStruct AdcService;


    typedef struct AdcServiceAdcListenerStruct AdcServiceAdcListener;
    struct AdcServiceAdcListenerStruct {
        EventListener base;
        AdcService   *adcService;
    };


    struct AdcServiceStruct {
        EventManager         *eventManager;
        AdcSource            *adcSource;
        AdcServiceAdcListener adcListener;
        AdcChannel           *channelListHead;
    };

    AdcService *AdcService_init(AdcService   *self,
                                EventManager *eventManager,
                                AdcSource    *adcSource);

    void AdcService_start(AdcService *self);

    AdcChannel *AdcService_initChannel(AdcService *self,
                                       AdcChannel *channel,
                                       int         channelId);




#ifdef __cplusplus
}
#endif

#endif
