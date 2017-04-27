/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/adc/AdcService.h>


static AdcService *_adcService = NULL;
static AdcService *(*_serviceFetcher)(void) = NULL;


/**
 *
 */
void SysAdcService_setup(AdcService *(*serviceFetcher)(void)) {

    _serviceFetcher = serviceFetcher;
}


/**
 *
 */
AdcService *SysAdcService_get() {

    if ( _adcService == NULL ) {
        _adcService = _serviceFetcher();
    }

    return _adcService;
}

