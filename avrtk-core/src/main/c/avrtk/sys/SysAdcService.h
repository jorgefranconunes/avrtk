/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef SYSTADCSERVICE_H
#define SYSADCSERVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcService.h>





    void SysAdcService_init(bool     (*startAdc)(int),
                            bool     (*isAdcCompleted)(void),
                            uint16_t (*getLatestAdcValue)(void));

    AdcService *SysAdcService_get(void);

    void SysAdcService_reset(void);





#ifdef __cplusplus
}
#endif

#endif
