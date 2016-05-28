/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>

#include <avr/interrupt.h>
#include <util/delay.h>





#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

#define BLINK_DELAY_MS 1000L

static long getTickCount(void);
static void setupAtmega328pTimer(void);

static long volatile _tickCount = 0;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int main() {

    int i;
    DDRD |= (1 << PD6);
    TCCR0A |= (1 << WGM00); // phase correct pwm
    TCCR0A |= (1 << COM0A1); // non-inverting mode
    TCCR0B |= (1 << CS01); // prescale factor of 8
    for(;;) {
    	for (i = 1; i < 256; i++) {
            OCR0A = i; // set duty cycle
            _delay_ms(3);
        }
    	for (i = 254; i>=0; --i) {
            OCR0A = i; // set duty cycle
            _delay_ms(3);
        }
    }
    return 0;



    setupAtmega328pTimer();

    /* Set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);
    PORTB |= _BV(PORTB5);

    long previousTickCount = 0L;

    for (;;) {
        /* long tickCount = getTickCount(); */

        /* if ( previousTickCount != tickCount ) { */
        /*     long ticks     = tickCount % BLINK_DELAY_MS; */
        /*     bool isLedOn   = ticks > (BLINK_DELAY_MS/2); */

        /*     if ( isLedOn ) { */
        /*         PORTD |= _BV(PORTD5); */
        /*     } else { */
        /*         PORTD &= ~_BV(PORTD5); */
        /*     } */

        /*     previousTickCount = tickCount; */
        /* } */
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void setupAtmega328pTimer() {


    cli();

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
  
    OCR1A = 31250;            // compare match register 16MHz/256/2Hz
    TCCR1B |= (1 << WGM12);   // CTC mode
    TCCR1B |= (1 << CS12);    // 256 prescaler 
    TIMSK1 |= (1 << OCIE1A);

    sei();
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

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





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

ISR (TIMER1_COMPA_vect) {

    ++_tickCount;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

