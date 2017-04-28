/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#ifndef CALLBACKADCLISTENER_H
#define CALLBACKADCLISTENER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <avrtk/adc/AdcListener.h>


    typedef struct CallbackAdcListenerStruct CallbackAdcListener;

    struct CallbackAdcListenerStruct {
        AdcListener   base;
        void (*callback)(AdcSample *sample);
    };

    CallbackAdcListener *CallbackAdcListener_init(
            CallbackAdcListener *self,
            void (*callback)(AdcSample *sample));

    AdcListener *CallbackAdcListener_asAdcListener(CallbackAdcListener *self);





#ifdef __cplusplus
}
#endif

#endif

