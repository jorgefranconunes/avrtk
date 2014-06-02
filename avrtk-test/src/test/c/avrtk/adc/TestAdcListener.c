/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/TestAdcListener.h>





static AdcListenerInterface interface = {
    .notify= &TestAdcListener_notify
};





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TestAdcListener *TestAdcListener_init(TestAdcListener *self) {

    self->base.vtable = &interface;
    self->notifyCount = 0;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void TestAdcListener_notify(AdcListener *baseSelf,
                            AdcSample   *sample) {

    TestAdcListener *self = (TestAdcListener *)baseSelf;

    AdcSample_initFromSample(&self->sample, sample);
    ++self->notifyCount;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcSample *TestAdcListener_getSample(TestAdcListener *self) {

    AdcSample *result = &self->sample;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int TestAdcListener_getNotifyCount(TestAdcListener *self) {

    long result = self->notifyCount;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcListener *TestAdcListener_asAdcListener(TestAdcListener *self) {

    AdcListener *result = (AdcListener *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

