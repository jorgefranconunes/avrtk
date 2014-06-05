/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/CallbackAdcListener.h>





static AdcListenerInterface interface = {
    .notify = &CallbackAdcListener_notify
};





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

CallbackAdcListener *
CallbackAdcListener_init(CallbackAdcListener *self,
                         void               (*callback)(AdcSample *sample)) {

    self->base.vtable = &interface;
    self->callback    = callback;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcListener *CallbackAdcListener_asAdcListener(CallbackAdcListener *self) {

    AdcListener *result = (AdcListener *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void CallbackAdcListener_notify(AdcListener *baseSelf,
                                AdcSample   *sample) {

    CallbackAdcListener *self = (CallbackAdcListener *)baseSelf;

    self->callback(sample);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

