/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
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
        void (*notify)(AdcListener *, AdcSample *);
    };

    struct AdcListenerStruct {
        AdcListenerInterface *vtable;
        AdcListener          *next;
    };

    void AdcListener_notify(AdcListener *self,
                            AdcSample   *sample);





#ifdef __cplusplus
}
#endif

#endif
