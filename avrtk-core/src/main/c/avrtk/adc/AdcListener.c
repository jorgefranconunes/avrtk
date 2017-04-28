/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/AdcListener.h>


/**
 * Called when a sample is available from the A/D converter.
 */
void AdcListener_onSample(
        AdcListener *self,
        AdcSample   *sample) {

    self->vtable->onSample(self, sample);
}

