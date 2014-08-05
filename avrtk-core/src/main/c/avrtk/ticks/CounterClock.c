/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/ticks/CounterClock.h
 *
 * @brief Definition of the CounterClock class methods.
 *
 **************************************************************************/

#include <avrtk/ticks/CounterClock.h>





/**********************************************************************//**
 *
 * @class CounterClock avrtk/ticks/CounterClock.h <avrtk/ticks/CounterClock.h>
 * @implements Clock
 * @ingroup avrtk_ticks
 *
 * @brief A concrete Clock that calculates time from an externally
 * provided counter.
 *
 **************************************************************************/





static ClockInterface interface = {
    .currentTimeMillis = CounterClock_currentTimeMillis
};





/**********************************************************************//**
 *
 * Initializes a CounterClock object.
 *
 * The increment factor is the number of milliseconds per tick.
 *
 * The increment factor is specified as a rational number:
 * incrementFactorN / incrementFactorD. This means that time
 * (milliseconds) grows by incrementeFactorN per each incrementFactorD
 * ticks.
 *
 * @public @memberof CounterClock
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





/**********************************************************************//**
 *
 * Updates the clock current time.
 *
 * The tick count received is expected to not be less than the
 * previous tick count this method was called with. Otherwise the
 * behaviour is undefined.
 *
 * @public @memberof CounterClock
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





/**********************************************************************//**
 *
 * Casts a CounterClock reference to a Clock reference.
 *
 * @public @memberof CounterClock
 *
 * @param self Reference to the object.
 *
 * @return A reference to the same CallbackTask object this method was
 * called for.
 *
 **************************************************************************/

Clock *CounterClock_asClock(CounterClock *self) {

    Clock *result = (Clock *)self;

    return result;
}





/**********************************************************************//**
 *
 * Retrieves the current time, as calculated from the latest values
 * passed to the CounterClock_update() method.
 *
 * This is the implementation of method Clock_currentTimeMillis().
 *
 * @public @memberof CounterClock
 *
 * @param baseSelf
 *
 **************************************************************************/

long CounterClock_currentTimeMillis(Clock *baseSelf) {

    CounterClock *self   = (CounterClock *)baseSelf;
    long          result = self->time;

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

