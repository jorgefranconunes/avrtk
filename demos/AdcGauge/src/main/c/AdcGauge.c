/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *
 * Set of 6 LEDs act as a gauge whose value is the ADC sample coming
 * out of a potentiometer.
 *
 **************************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include <avr/io.h>

#include <avrtk/adc/CallbackAdcListener.h>

#include <avrtk/sys/SysAdcService.h>
#include <avrtk/sys/SysEventManager.h>
#include <avrtk/sys/atm328p/Atm328pAdcService.h>





static const int  ADC_CHANNEL_ID = 0;


static void setupAdcListener(void);
static void adcCallback(AdcSample *sample);


static int _patternMask = 0b11111100;
static int _maxBarCount    = 6;

static AdcChannel          _adcChannelData;
static CallbackAdcListener _callbackAdcListenerData;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int main() {

    Atm328pAdcService_init();

    /* Set the appropriate pins of PORTD for output*/
    DDRD |= _patternMask;

    setupAdcListener();

    /* Run forever. */
    SysEventManager_start();
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void setupAdcListener() {

    AdcService *adcService = SysAdcService_get();
    AdcChannel *adcChannel =
        AdcService_initChannel(adcService, &_adcChannelData, ADC_CHANNEL_ID);

    CallbackAdcListener *callbackAdcListener =
        CallbackAdcListener_init(&_callbackAdcListenerData, &adcCallback);
    AdcListener         *adcListener         =
        CallbackAdcListener_asAdcListener(callbackAdcListener);

    AdcChannel_addListener(adcChannel, adcListener);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void adcCallback(AdcSample *sample) {

    uint16_t sampleValue = AdcSample_getValue(sample);
    uint16_t scaledValue = sampleValue >> (16-_maxBarCount);
    uint16_t value       = _maxBarCount * scaledValue / ((1<<_maxBarCount) - 1);

    uint8_t gauge = 0;

    for ( int i=0; i<value; ++i ) {
        gauge = (gauge<<1) | 0x01;
    }

    PORTD = (PORTD & ~_patternMask) | (gauge<<2);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

