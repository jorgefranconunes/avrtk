/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include <avrtk/sys/SysEventManager.h>
#include <avrtk/sys/SysTickSource.h>
#include <avrtk/tasks/TickTaskService.h>





static void init(void);

static bool            _isInited = false;
static TickTaskService _taskServiceData;
static TaskService    *_taskService = NULL;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

TaskService *SysTaskService_get () {

    init();

    return _taskService;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void init() {

    if ( _isInited ) {
        return;
    }

    EventManager    *eventManager     = SysEventManager_get();
    Clock           *clock            = SysTickSource_getClock();
    TickTaskService *tickTaskService  =
        TickTaskService_init(&_taskServiceData, eventManager, clock);
    TaskService     *taskService      =
        TickTaskService_asTaskService(tickTaskService);

    TaskService_start(taskService);

    _taskService = taskService;
    _isInited    = true;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void SysTaskService_reset() {

    _taskService = NULL;
    _isInited    = false;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

