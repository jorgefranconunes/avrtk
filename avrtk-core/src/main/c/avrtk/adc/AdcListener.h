/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef ADCLISTENER_H
#define ADCLISTENER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcSample.h>


    typedef struct AdcListenerStruct AdcListener;

    typedef struct AdcListenerInterfaceStruct AdcListenerInterface;
    struct AdcListenerInterfaceStruct {
        void (*onSample)(AdcListener *, AdcSample *);
    };

    struct AdcListenerStruct {
        AdcListenerInterface *vtable;
        AdcListener          *next;
    };

    void AdcListener_onSample(
            AdcListener *self,
            AdcSample *sample);


#ifdef __cplusplus
}
#endif

#endif
