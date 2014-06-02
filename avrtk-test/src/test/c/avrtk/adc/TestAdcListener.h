/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
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
        int         notifyCount;
    };


    TestAdcListener *TestAdcListener_init(TestAdcListener *self);

    void TestAdcListener_notify(AdcListener *self,
                                AdcSample   *sample);

    AdcSample *TestAdcListener_getSample(TestAdcListener *self);

    int TestAdcListener_getNotifyCount(TestAdcListener *self);

    AdcListener *TestAdcListener_asAdcListener(TestAdcListener *self);





#ifdef __cplusplus
}
#endif

#endif