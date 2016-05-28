/**************************************************************************
 *
 * Copyright (c) 2014-2016 Jorge Nunes, All Rights Reserved.
 *
 *
 * Proof of concept for using TIMER0 and the ADC.
 *
 **************************************************************************/

#include <stdbool.h>

#include <avr/interrupt.h>


static void updateGauge(uint16_t value);
static void updateAdc(void);
static void setupAtm328Adc(void);
static void startAtm328AdcConversion(int channel);
static bool isAdcCompleted(void);
static uint16_t getLatestAdcValue();

static int _patternMask  = 0b11111100;
static int  _adcChannel = 0;
static bool _isAdcFirstTime = true;

// The following are used inside interrupt routines.
static bool     volatile _isAdcCompleted = false;
static uint16_t volatile _adcValue = 0;


/**
 *
 */
int main() {

    setupAtm328Adc();

    /* Set the appropriate pins of PORTD for output*/
    DDRD |= _patternMask;

    for (;;) {
        updateAdc();
    }
}


/**
 *
 */
static void updateGauge(uint16_t value) {

    uint8_t gauge = 0;

    for ( uint16_t remainder = value >> 10;
          remainder > 0;
          remainder >>= 1 ) {
        gauge = (gauge<<1) | 0x01;
    }

    PORTD = (PORTD & ~_patternMask) | (gauge<<2);
}


/**
 *
 */
static void updateAdc() {

    if ( _isAdcFirstTime ) {
        _isAdcFirstTime = false;
        startAtm328AdcConversion(_adcChannel);
    } else {
        if ( isAdcCompleted() ) {
            uint16_t value = getLatestAdcValue();

            updateGauge(value);
            startAtm328AdcConversion(_adcChannel);
        }
    }
}


/**
 *
 */
static void setupAtm328Adc() {

    cli();

    // Disable Power reduction ADC
    PRR &= ~_BV(PRADC);

    // Use AVCC as Voltage Reference Selection. REFS1:REFS0 = 0x01
    ADMUX = (ADMUX & 0x3f) | 0x40;

    // ADC Left Adjust Result is off.
    ADMUX &= ~_BV(ADLAR);

    // ADC Enable is on.
    ADCSRA |= _BV(ADEN);

    // Set the prescaler to 128.
    ADCSRA = (ADCSRA & 0xf8) | 0x07;

    // ADC Auto Trigger Enable is off to start a single conversion.
    ADCSRA &= ~_BV(ADATE);

    // ADC Interrupt Enable is on, wo we will get an interrupt when
    // the conversion completes.
    ADCSRA |= _BV(ADIE);

    sei();
}


/**
 *
 */
static void startAtm328AdcConversion(int channel) {

    _isAdcCompleted = false;

    // Set the corresponding pin in port C as input.
    if ( channel < 8 ) {
        DDRC &= ~_BV(channel);
    }

    // Analog Chnnel Selection Bits set to channel number.
    ADMUX = (ADMUX & 0xf0) | (channel & 0x0f);

    // And start the conversion by setting the ADC Start Conversion bit.
    ADCSRA |= _BV(ADSC);
}


/**
 *
 */
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


/**
 *
 */
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


/**
 *
 */
ISR (ADC_vect) {

    uint16_t lowByte  =  ADCL;
    uint16_t hiByte   =  ADCH;
    uint16_t atmValue = (hiByte<<8) | lowByte;

    _adcValue       = atmValue << 6 | 0x3f;
    _isAdcCompleted = true;
}
