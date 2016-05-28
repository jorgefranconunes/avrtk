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


static const long MIN_DELAY = 200L;
static const long MAX_DELAY = 2000L;


static void updateLed(void);
static long getTickCount(void);
static void setupAtm328pTimer(void);

static void updateAdc(void);
static void setupAtm328Adc(void);
static void startAtm328AdcConversion(int channel);
static bool isAdcCompleted(void);
static uint16_t getLatestAdcValue();

static long     volatile _tickCount = 0L;
static bool     volatile _isAdcCompleted = false;
static uint16_t volatile _adcValue = 0;

static long _previousTickCount = 0L;
static long _blinkDelay = 1000L;
static long _nextBlinkDelay = 1000L;
static bool _ledState = false;
static int  _adcChannel = 0;
static bool _isAdcFirstTime = true;


/**
 *
 */
int main() {

    setupAtm328pTimer();
    setupAtm328Adc();

    /* Set pin 5 of PORTD for output*/
    DDRD |= _BV(DDD5);

    for (;;) {
        updateLed();
        updateAdc();
    }
}


/**
 *
 */
static void updateLed() {

    long tickCount = getTickCount();

    if ( _previousTickCount != tickCount ) {
        bool nextLedState   = (tickCount%_blinkDelay) > (_blinkDelay/2);

        if ( nextLedState != _ledState ) {
            _ledState = nextLedState;
            if ( _ledState ) {
                PORTD |= _BV(PORTD5);
            } else {
                PORTD &= ~_BV(PORTD5);
            }
            _blinkDelay = _nextBlinkDelay;
        }

        _previousTickCount = tickCount;
    }
}


/**
 *
 */
static void setupAtm328pTimer() {

    cli();

    // Set Timer 0 Mode to CTC
    TCCR0A |= _BV(WGM01);

    // Select CLK/64 prescaler.
    TCCR0B |= _BV(CS01) | _BV(CS00);

    // Set Output Compare Register A for 1KHz timer.
    OCR0A = 0xF9;

    // Enable TIMER0_COMPA interrupt for each tick of Timer 0.
    TIMSK0 |= _BV(OCIE0A);

    sei();
}


/**
 *
 */
static long getTickCount() {

    long result;

    uint8_t currSREG = SREG;
    cli();

    /**
     ** Start of exclusive block.
     **/

    result = _tickCount;

    /**
     ** End of exclusive block.
     **/

    SREG = currSREG;

    return result;
}


/**
 *
 */
ISR (TIMER0_COMPA_vect) {

    ++_tickCount;
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
            uint16_t value    = getLatestAdcValue();
            long     newDelay =
                MIN_DELAY + (MAX_DELAY-MIN_DELAY)*value / 0xffff;

            _nextBlinkDelay = newDelay;
            startAtm328AdcConversion(_adcChannel);
        }
    }
}


/**
 *
 */
static void setupAtm328Adc() {

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
