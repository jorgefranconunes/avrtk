/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef TESTTADCLISTENER_H
#define TESTADCLISTENER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcListener.h>


    typedef struct TestAdcListenerStruct TestAdcListener;

    struct TestAdcListenerStruct {
        AdcListener base;
        AdcSample   sample;
        int         eventCount;
    };


    TestAdcListener *TestAdcListener_init(TestAdcListener *self);

    AdcSample *TestAdcListener_getSample(TestAdcListener *self);

    int TestAdcListener_getEventCount(TestAdcListener *self);

    AdcListener *TestAdcListener_asAdcListener(TestAdcListener *self);


#ifdef __cplusplus
}
#endif

#endif
