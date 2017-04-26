/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef ADCSERVICE_H
#define ADCSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcChannel.h>
#include <avrtk/events/EventListener.h>
#include <avrtk/events/EventManager.h>


    typedef struct AdcServiceStruct AdcService;


    typedef struct AdcServiceInterfaceStruct AdcServiceInterface;
    struct AdcServiceInterfaceStruct {
        void (*start)(AdcService *self);
        AdcChannel *(*initChannel)(
                AdcService *self,
                AdcChannel *channel,
                int channelId);
    };


    struct AdcServiceStruct {
        AdcServiceInterface *vtable;
    };

    void AdcService_start(AdcService *self);

    AdcChannel *AdcService_initChannel(
            AdcService *self,
            AdcChannel *channel,
            int channelId);


#ifdef __cplusplus
}
#endif

#endif
