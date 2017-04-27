/**************************************************************************
 *
 * Copyright (c) 2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef BASICADCSERVICESINGLETON_H
#define BASICADCSERVICESINGLETON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcService.h>
#include <avrtk/events/EventManager.h>


    AdcService *BasicAdcServiceSingleton_setup(
            EventManager *eventManager,
            bool (*startAdc)(int),
            bool (*isAdcCompleted)(void),
            uint16_t (*getLatestAdcValue)(void));


#ifdef __cplusplus
}
#endif

#endif
