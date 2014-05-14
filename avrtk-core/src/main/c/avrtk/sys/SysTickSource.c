/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include <avrtk/sys/SysEventManager.h>
#include <avrtk/ticks/CounterTickSource.h>





static bool               _needsInit = true;
static CounterTickSource  _tickSourceData;
static CounterTickSource *_tickSource = NULL;
static Clock             *_clock      = NULL;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void SysTickSource_init(long (*tickCountGetter)(void),
                        int    incrementFactorN,
                        int    incrementFactorD) {

    CounterTickSource *tickSource =
        CounterTickSource_init(&_tickSourceData,
                               tickCountGetter,
                               incrementFactorN,
                               incrementFactorD);
    Clock *clock =
        CounterTickSource_getClock(tickSource);

    EventManager *eventManager =
        SysEventManager_get();

    EventManager_addSource(eventManager,
                           CounterTickSource_asEventSource(tickSource));

    _tickSource = tickSource;
    _clock      = clock;
    _needsInit  = false;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventSource *SysTickSource_get() {

    assert( _needsInit == false );

    EventSource *result = CounterTickSource_asEventSource(_tickSource);

    return result;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

Clock *SysTickSource_getClock() {

    assert( _needsInit == false );

    return _clock;
}





/**************************************************************************
 *
 * Restores the state as it was prior to calling the
 * <code>SysTickSource_init(...)</code> function.
 *
 * <p>After calling this function, the
 * <code>SysTickSource_init(...)</code> needs to be called before
 * attempting to invoke any other functions.</p>
 *
 * <p>This function would not usually be called in a production
 * application. But it is usefull in test environment.</p>
 *
 **************************************************************************/

void SysTickSource_reset() {

    _tickSource = NULL;
    _clock      = NULL;
    _needsInit  = true;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

