/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/TestAdcListener.h>


static void TestAdcListener_onSample(
        AdcListener *baseSelf,
        AdcSample   *sample);

static AdcListenerInterface interface = {
    .onSample= &TestAdcListener_onSample
};


/**
 *
 */
TestAdcListener *TestAdcListener_init(TestAdcListener *self) {

    self->base.vtable = &interface;
    self->notifyCount = 0;

    return self;
}


/**
 *
 */
static void TestAdcListener_onSample(
        AdcListener *baseSelf,
        AdcSample   *sample) {

    TestAdcListener *self = (TestAdcListener *)baseSelf;

    AdcSample_initFromSample(&self->sample, sample);
    ++self->notifyCount;
}


/**
 *
 */
AdcSample *TestAdcListener_getSample(TestAdcListener *self) {

    AdcSample *result = &self->sample;

    return result;
}


/**
 *
 */
int TestAdcListener_getNotifyCount(TestAdcListener *self) {

    long result = self->notifyCount;

    return result;
}


/**
 *
 */
AdcListener *TestAdcListener_asAdcListener(TestAdcListener *self) {

    AdcListener *result = (AdcListener *)self;

    return result;
}

