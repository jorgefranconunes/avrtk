/**************************************************************************
 *
 * Copyright (c) 2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef BASICADCSERVICE_H
#define BASICADCSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcChannel.h>
#include <avrtk/adc/AdcService.h>
#include <avrtk/adc/BasicAdcSource.h>
#include <avrtk/events/EventListener.h>
#include <avrtk/events/EventManager.h>


    typedef struct BasicAdcServiceStruct BasicAdcService;


    typedef struct AdcServiceAdcListenerStruct AdcServiceAdcListener;
    struct AdcServiceAdcListenerStruct {
        EventListener base;
        BasicAdcService *adcService;
    };


    struct BasicAdcServiceStruct {
        AdcService base;
        EventManager *eventManager;
        BasicAdcSource *adcSource;
        AdcServiceAdcListener adcListener;
        AdcChannel *channelListHead;
    };

    BasicAdcService *BasicAdcService_init(
            BasicAdcService *self,
            EventManager *eventManager,
            BasicAdcSource *adcSource);

    AdcService *BasicAdcService_asAdcService(BasicAdcService *self);


#ifdef __cplusplus
}
#endif

#endif
