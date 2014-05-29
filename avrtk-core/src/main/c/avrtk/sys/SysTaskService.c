/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include <avrtk/sys/SysEventManager.h>
#include <avrtk/sys/SysTickSource.h>
#include <avrtk/tasks/TaskService.h>





static void init(void);

static bool         _isInited = false;
static TaskService  _taskServiceData;
static TaskService *_taskService = NULL;





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

    EventManager *eventManager = SysEventManager_get();
    Clock        *clock        = SysTickSource_getClock();
    TaskService  *taskService  =
        TaskService_init(&_taskServiceData, eventManager, clock);

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

