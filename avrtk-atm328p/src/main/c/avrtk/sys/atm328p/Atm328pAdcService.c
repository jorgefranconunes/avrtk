/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>

#include <avr/interrupt.h>

#include <avrtk/sys/SysAdcService.h>





static bool     startAdc(int);
static bool     isAdcCompleted(void);
static uint16_t getLatestAdcValue(void);
static void     startAtm328AdcConversion(int channel);

static bool _isInited = false;

static volatile bool     _isAdcCompleted = false;
static volatile uint16_t _adcValue       = 0;





/**************************************************************************
 *
 * Initializes the system ADC service. Only after calling this
 * function you can safely call <code>SysAdcService_get()</code>
 *
 * It is ok to call this function more than once. Only the first call
 * will have an effect.
 *
 **************************************************************************/

void Atm328pAdcService_init() {

    if ( !_isInited ) {
        SysAdcService_init(&startAdc, &isAdcCompleted, &getLatestAdcValue);

        _isInited = true;
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static bool startAdc(int channelId) {

    bool isOk = true;

    if ( (channelId>=0) && (channelId<=8) ) {
        startAtm328AdcConversion(channelId);
    } else {
        isOk = false;
    }

    return isOk;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void startAtm328AdcConversion(int channel) {

    // Set the corresponding pin in port C as input.
    if ( channel < 8 ) {
        DDRC &= ~_BV(channel);
    }

    // Disable Power reduction ADC
    PRR &= ~_BV(PRADC);

    // Use AVCC as Voltage Reference Selection. REFS1:REFS0 = 0x00
    ADMUX &= ~(_BV(REFS1) | _BV(REFS0));

    // ADC Left Adjust Result is off.
    ADMUX &= ~_BV(ADLAR);

    // Analog Chnnel Selection Bits set to channel number.
    ADMUX = (ADMUX & 0xf) | (channel & 0x0f);

    // ADC Enable is on.
    ADCSRA |= _BV(ADEN);

    // ADC Auto Trigger Enable is off to start a single conversion.
    ADCSRA &= ~_BV(ADATE);

    // ADC Interrupt Enable is on, wo we will get an interrupt when
    // the conversion completes.
    ADCSRA |= _BV(ADIE);

    // And start the conversion by setting the ADC Start Conversion bit.
    ADCSRA |= _BV(ADSC);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static bool isAdcCompleted() {

    bool result;

    uint8_t currSREG = SREG;
    cli();

    /**
     ** Start of exclusive block.
     **/

    result = _isAdcCompleted;

    /**
     ** End of exclusive block.
     **/

    SREG = currSREG;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static uint16_t getLatestAdcValue() {

    uint16_t result;

    uint8_t currSREG = SREG;
    cli();

    /**
     ** Start of exclusive block.
     **/

    result = _adcValue;

    /**
     ** End of exclusive block.
     **/

    SREG = currSREG;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

ISR (ADC_vect) {

    uint16_t lowByte = ADCL;
    uint16_t hiByte  = ADCH;

    _adcValue       = (hiByte<<8) | lowByte;
    _isAdcCompleted = true;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/
