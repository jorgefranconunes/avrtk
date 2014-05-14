/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>

#include <avr/interrupt.h>

#include <avrtk/sys/SysTickSource.h>





#define INCREMENT_FACTOR_N 1
#define INCREMENT_FACTOR_D 1

static long getTickCount(void);
static void setupAtmega328pTimer(void);

static bool _isInited = false;
static long volatile _tickCount = 0;





/**************************************************************************
 *
 * Initializes the system tick source. Only after calling this
 * function you can safely call <code>SysTickSource_get()</code>
 *
 * It is ok to call this function more than once. Only the first call
 * will have an effect.
 *
 **************************************************************************/

void Atm328pTickSource_init() {

    if ( !_isInited ) {
        SysTickSource_init(&getTickCount,
                           INCREMENT_FACTOR_N,
                           INCREMENT_FACTOR_D);
        setupAtmega328pTimer();

        _isInited = true;
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

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





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static long getTickCount(void) {

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





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

ISR (TIMER0_COMPA_vect) {

    ++_tickCount;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

