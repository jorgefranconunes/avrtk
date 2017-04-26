/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include <avrtk/adc/BasicAdcService.h>
#include <avrtk/adc/BasicAdcSource.h>
#include <avrtk/sys/SysAdcService.h>
#include <avrtk/sys/SysEventManager.h>


static bool _isInited = true;
static BasicAdcSource _adcSourceData;
static BasicAdcService _basicAdcServiceData;
static AdcService *_adcService = NULL;


/**
 *
 */
void SysAdcService_init(
        bool (*startAdc)(int),
        bool (*isAdcCompleted)(void),
        uint16_t (*getLatestAdcValue)(void)) {

    EventManager *eventManager = SysEventManager_get();
    BasicAdcSource *adcSource = BasicAdcSource_init(
            &_adcSourceData,
            startAdc,
            isAdcCompleted,
            getLatestAdcValue);
    BasicAdcService *basicAdcService   =
        BasicAdcService_init(&_basicAdcServiceData, eventManager, adcSource);
    AdcService *adcService = BasicAdcService_asAdcService(basicAdcService);

    EventManager_addSource(
            eventManager,
            BasicAdcSource_asEventSource(adcSource));
    AdcService_start(adcService);

    _adcService = adcService;
    _isInited   = true;
}


/**
 *
 */
AdcService *SysAdcService_get() {

    assert( _isInited == false );

    return _adcService;
}


/**
 * Restores the state as it was prior to calling the
 * <code>SysAdcService_init(...)</code> function.
 *
 * <p>After calling this function, the
 * <code>SysAdcService_init(...)</code> needs to be called before
 * attempting to invoke any other functions.</p>
 *
 * <p>This function would not usually be called in a production
 * application. But it is usefull in test environment.</p>
 */
void SysAdcService_reset() {

    _adcService = NULL;
    _isInited   = true;
}

