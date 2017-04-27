/**************************************************************************
 *
 * Copyright (c) 2014-2017 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>

#include <avr/interrupt.h>

#include <avrtk/adc/BasicAdcServiceSingleton.h>
#include <avrtk/sys/SysAdcService.h>
#include <avrtk/sys/SysEventManager.h>


static AdcService *Atm328pAdcService_get(void);
static void setupAtm328Adc(void);
static bool startAdc(int);
static bool isAdcCompleted(void);
static uint16_t getLatestAdcValue(void);
static void startAtm328AdcConversion(int channel);

// These are modified only within the ADC_vect interrupt handler.
static volatile bool _isAdcCompleted = false;
static volatile uint16_t _adcValue = 0;


/**
 * Initializes the system ADC service.
 *
 * It is ok to call this function more than once. Only the first call
 * will have an effect.
 */
void Atm328pAdcService_setup() {

    SysAdcService_setup(&Atm328pAdcService_get);
}


/**
 * This function is supposed to be called only once.
 */
static AdcService *Atm328pAdcService_get() {

    setupAtm328Adc();

    AdcService *adcService = BasicAdcServiceSingleton_setup(
            SysEventManager_get(),
            &startAdc,
            &isAdcCompleted,
            &getLatestAdcValue);

    return adcService;
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

    // ADC Interrupt Enable is on, so we will get an interrupt when
    // the conversion completes.
    ADCSRA |= _BV(ADIE);

    sei();
}


/**
 * Initiates one conversion on the given channel.
 */
static bool startAdc(int channelId) {

    bool isOk = true;

    if ( (channelId>=0) && (channelId<=8) ) {
        startAtm328AdcConversion(channelId);
    } else {
        isOk = false;
    }

    return isOk;
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

    uint16_t lowByte  = ADCL;
    uint16_t hiByte   = ADCH;
    uint16_t atmValue =(hiByte<<8) | lowByte;

    _adcValue       = atmValue << 6;
    _isAdcCompleted = true;
}

