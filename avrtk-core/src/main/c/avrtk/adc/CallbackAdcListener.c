/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/CallbackAdcListener.h>


static void CallbackAdcListener_onSample(
        AdcListener *baseSelf,
        AdcSample   *sample);

static AdcListenerInterface interface = {
    .onSample = &CallbackAdcListener_onSample
};


/**
 *
 */
CallbackAdcListener *CallbackAdcListener_init(
        CallbackAdcListener *self,
        void (*callback)(AdcSample *sample)) {

    self->base.vtable = &interface;
    self->callback = callback;

    return self;
}


/**
 *
 */
AdcListener *CallbackAdcListener_asAdcListener(CallbackAdcListener *self) {

    AdcListener *result = (AdcListener *)self;

    return result;
}


/**
 *
 */
static void CallbackAdcListener_onSample(
        AdcListener *baseSelf,
        AdcSample   *sample) {

    CallbackAdcListener *self = (CallbackAdcListener *)baseSelf;

    self->callback(sample);
}

