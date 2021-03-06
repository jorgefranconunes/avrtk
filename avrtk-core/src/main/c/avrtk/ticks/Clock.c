/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *//**
 *
 * @file avrtk/ticks/Clock.h
 *
 * @brief Definition of the Clock interface methods.
 *
 **************************************************************************/

#include <avrtk/ticks/Clock.h>





/**********************************************************************//**
 *
 * @interface Clock avrtk/ticks/Clock.h <avrtk/ticks/Clock.h>
 * @ingroup avrtk_ticks
 *
 * @brief Provides access to the system time.
 *
 **************************************************************************/





/**********************************************************************//**
 *
 * Retrieves the current system time.
 *
 * @public @memberof Clock
 * @pure
 *
 * There are no guarantees on the time origin. The contract for this
 * method is that the difference between values returned by two calls
 * correspond to the time interval, in milliseconds, between those two
 * calls.
 *
 * @param self Reference to the Clock object to be queried.
 *
 **************************************************************************/

long Clock_currentTimeMillis(Clock *self) {

    return self->vtable->currentTimeMillis(self);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

