/**************************************************************************
 *
 * Copyright (c) 2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/BasicAdcService.h>
#include <avrtk/adc/BasicAdcSource.h>
#include <avrtk/events/EventManager.h>


static BasicAdcSource _adcSourceData;
static BasicAdcService _adcServiceData;


/**
 * Only the first call to this method has any effect.
 */
AdcService *BasicAdcServiceSingleton_setup(
        EventManager *eventManager,
        bool (*startAdc)(int),
        bool (*isAdcCompleted)(void),
        uint16_t (*getLatestAdcValue)(void)) {

    BasicAdcSource *adcSource = BasicAdcSource_init(
            &_adcSourceData,
            startAdc,
            isAdcCompleted,
            getLatestAdcValue);
    BasicAdcService *basicAdcService = BasicAdcService_init(
            &_adcServiceData, eventManager, adcSource);
    AdcService *adcService = BasicAdcService_asAdcService(basicAdcService);

    EventManager_addSource(
            eventManager,
            BasicAdcSource_asEventSource(adcSource));
    AdcService_start(adcService);

    return adcService;
}

