/**************************************************************************
 *
 * Copyright (c) 2014-2016 Jorge Nunes, All Rights Reserved.
 *
 *
 * The archetypal "hello, world" for the embeded world.
 *
 * This program blinks port 5 on the Arduino board. That's pin PD5 on
 * the Atmega328P.
 *
 **************************************************************************/

#include <avr/io.h>
#include <util/delay.h>


const double BLINK_DELAY_MS = 500.0;


/**
 * 
 */
int main (void) {

    /* Set pin 5 of PORTD for output*/
    DDRD |= _BV(DDD5);

    while(1) {
        /* Set pin 5 high to turn led on */
        PORTD |= _BV(PORTD5);
        _delay_ms(BLINK_DELAY_MS);

        /* Set pin 5 low to turn led off */
        PORTD &= ~_BV(PORTD5);
        _delay_ms(BLINK_DELAY_MS);
    }

    return 0;
}

