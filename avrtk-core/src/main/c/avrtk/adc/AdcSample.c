/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/adc/AdcSample.h>





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcSample *AdcSample_init(AdcSample *self,
                          int        channelId,
                          uint16_t   value) {

    self->channelId = channelId;
    self->value     = value;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

AdcSample *AdcSample_initFromSample(AdcSample *self,
                                    AdcSample *sample) {

    self->channelId = sample->channelId;
    self->value     = sample->value;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int AdcSample_getChannelId(AdcSample *self) {

    return self->channelId;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

uint16_t AdcSample_getValue(AdcSample *self) {

    return self->value;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

