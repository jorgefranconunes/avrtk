/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef SYSTADCSERVICE_H
#define SYSADCSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcService.h>


    void SysAdcService_setup(AdcService *(*serviceFetcher)(void));

    AdcService *SysAdcService_get(void);


#ifdef __cplusplus
}
#endif

#endif
