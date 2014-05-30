/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef ADCEVENT_H
#define ADCEVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcSample.h>
#include <avrtk/events/Event.h>





    typedef struct AdcEventStruct AdcEvent;
    struct AdcEventStruct {
        Event     base;
        AdcSample sample;
    };

    AdcEvent *AdcEvent_init(AdcEvent *self,
                            int       channelId,
                            uint16_t  sampleValue);

    AdcSample *AdcEvent_getSample(AdcEvent *self);

    Event *AdcEvent_asEvent(AdcEvent *self);

    AdcEvent *AdcEvent_fromEvent(Event *baseSelf);





#ifdef __cplusplus
}
#endif

#endif
