/**************************************************************************
 *
 * Copyright (c) 2014-2016 Jorge Nunes, All Rights Reserved.
 *
 *
 * Proof of concept for using TIMER0 as tick counter.
 *
 * This program blinks port 5 on the Arduino board. That's pin PD5 on
 * the Atmega328P.
 *
 **************************************************************************/

#include <stdbool.h>

#include <avr/interrupt.h>


#define BLINK_DELAY_MS 1000L

static long getTickCount(void);
static void setupAtmega328pTimer(void);

static long volatile _tickCount = 0L;


/**
 *
 */
int main() {

    setupAtmega328pTimer();

    /* Set pin 5 of PORTD for output*/
    DDRD |= _BV(DDD5);

    long previousTickCount = 0L;

    for (;;) {
        long tickCount = getTickCount();

        if ( previousTickCount != tickCount ) {
            bool isLedOn   = (tickCount%BLINK_DELAY_MS) > (BLINK_DELAY_MS/2);

            if ( isLedOn ) {
                PORTD |= _BV(PORTD5);
            } else {
                PORTD &= ~_BV(PORTD5);
            }

            previousTickCount = tickCount;
        }
    }
}


/**
 * Sets up TIMER0 as 1 KHz timer.
 */
static void setupAtmega328pTimer() {

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
 * ISR called when TIMER0 ticks.
 */
ISR (TIMER0_COMPA_vect) {

    ++_tickCount;

    /* if ( (_tickCount%BLINK_DELAY_MS) > (BLINK_DELAY_MS/2) ) { */
    /*     PORTB &= ~_BV(PORTB0); */
    /* } else { */
    /*     PORTB |= _BV(PORTB0); */
    /* } */
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

