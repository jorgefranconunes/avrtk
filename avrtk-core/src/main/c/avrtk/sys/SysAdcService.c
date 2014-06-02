/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include <avrtk/adc/BasicAdcSource.h>
#include <avrtk/adc/AdcService.h>
#include <avrtk/sys/SysAdcService.h>
#include <avrtk/sys/SysEventManager.h>





static bool            _needsInit = true;
static BasicAdcSource _adcSourceData;
static AdcService      _adcServiceData;
static AdcService     *_adcService = NULL;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void SysAdcService_init(bool     (*startAdc)(int),
                        bool     (*isAdcCompleted)(void),
                        uint16_t (*getLatestAdcValue)(void)) {

    BasicAdcSource *basicAdcSource =
        BasicAdcSource_init(&_adcSourceData,
                            startAdc,
                            isAdcCompleted,
                            getLatestAdcValue);
    AdcSource      *adcSource    = BasicAdcSource_asAdcSource(basicAdcSource);
    EventManager   *eventManager = SysEventManager_get();

    _adcService = AdcService_init(&_adcServiceData, eventManager, adcSource);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcService *SysAdcService_get() {

    assert( _needsInit == false );

    return _adcService;
}





/**************************************************************************
 *
 * Restores the state as it was prior to calling the
 * <code>SysAdcService_init(...)</code> function.
 *
 * <p>After calling this function, the
 * <code>SysAdcService_init(...)</code> needs to be called before
 * attempting to invoke any other functions.</p>
 *
 * <p>This function would not usually be called in a production
 * application. But it is usefull in test environment.</p>
 *
 **************************************************************************/

void SysAdcService_reset() {

    _adcService = NULL;
    _needsInit  = true;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

