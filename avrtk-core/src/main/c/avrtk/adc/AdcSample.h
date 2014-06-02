/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef ADCSAMPLE_H
#define ADCSAMPLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>





    typedef struct AdcSampleStruct AdcSample;
    struct AdcSampleStruct {
        int      channelId;
        uint16_t value;
    };

    AdcSample *AdcSample_init(AdcSample *self,
                              int        channelId,
                              uint16_t   value);

    AdcSample *AdcSample_initFromSample(AdcSample *self,
                                        AdcSample *sample);

    int  AdcSample_getChannelId(AdcSample *self);

    uint16_t AdcSample_getValue(AdcSample *self);





#ifdef __cplusplus
}
#endif

#endif
