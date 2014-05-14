/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stddef.h>

#include <avrtk/sys/SysEventManager.h>





static EventManager  _eventManagerData;
static EventManager *_eventManager = NULL;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

EventManager *SysEventManager_get() {

    if ( NULL == _eventManager ) {
        _eventManager = EventManager_init(&_eventManagerData);
    }

    return _eventManager;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void SysEventManager_start() {

    EventManager *eventManager = SysEventManager_get();

    EventManager_start(eventManager);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void SysEventManager_reset() {

    _eventManager = NULL;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

