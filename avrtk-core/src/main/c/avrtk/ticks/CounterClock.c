/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/ticks/CounterClock.h>





static ClockInterface interface = {
    .currentTimeMillis = CounterClock_currentTimeMillis
};





/**************************************************************************
 *
 * The increment factor is the number of milliseconds per tick.
 *
 * The increment factor is specified as a rational number:
 * incrementFactorN / incrementFactorD. This means that time
 * (milliseconds) grows incrementeFactorN per incrementFactorD ticks.
 *
 * @param self Reference to the object being initialized.
 *
 * @param incrementFactorN The numerator of the time growth factor per
 * tick. Must not be zero.
 *
 * @param incrementFactorD The denominator of the time growth factor
 * per tick. Must not be zero.
 *
 **************************************************************************/

CounterClock *CounterClock_init(CounterClock *self,
                                int           incrementFactorN,
                                int           incrementFactorD) {

    self->base.vtable = &interface;
    self->incrFactorN = incrementFactorN;
    self->incrFactorD = incrementFactorD;
    self->ticks       = 0L;
    self->time        = 0L;

    return self;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

long CounterClock_currentTimeMillis(Clock *self) {

    CounterClock *me     = (CounterClock *)self;
    long          result = me->time;

    return result;
}





/**************************************************************************
 *
 * Updates the clock current time.
 *
 * The tick count received is expected to not be less than the
 * previous tick count this method was called with.
 *
 * @param self Reference to the object.
 *
 * @param currentTickCount The new number of ticks.
 *
 **************************************************************************/

void CounterClock_update(CounterClock *self,
                         long          currentTickCount) {

    int  fN    = self->incrFactorN;
    int  fD    = self->incrFactorD;
    long ticks = self->ticks;
    long time  = self->time;

    long counter = currentTickCount - fD;

    while ( counter >= ticks ) {
        ticks += fD;
        time  += fN;
    }

    self->ticks = ticks;
    self->time  = time;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

Clock *CounterClock_asClock(CounterClock *self) {

    Clock *result = (Clock *)self;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

