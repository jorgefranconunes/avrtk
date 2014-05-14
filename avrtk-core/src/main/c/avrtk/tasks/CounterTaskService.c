/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <avrtk/tasks/CounterTaskService.h>





static void CounterTaskService_start(TaskService *baseSelf);

static TaskServiceInterface interface = {
    .start = CounterTaskService_start
};





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

void CounterTaskService_init(CounterTaskService     *self,
                             CounterTaskServiceConf *conf) {

    CounterTickSource_init(&self->tickSource,
                           conf->tickCountGetter,
                           conf->incrementFactorN,
                           conf->incrementFactorD);

    Clock *clock = CounterTickSource_getClock(&self->tickSource);

    TaskService_init(&self->base, conf->eventManager, clock);
    self->base.vtable = &interface;

    self->eventManager    = conf->eventManager;
    self->tickCountIniter = conf->tickCountIniter;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void CounterTaskService_start(TaskService *baseSelf) {

    CounterTaskService *self        = (CounterTaskService *)self;
    EventSource        *eventSource =
        CounterTickSource_asEventSource(&self->tickSource);

    EventManager_addSource(self->eventManager, eventSource);
    self->tickCountIniter();
    TaskService_start(baseSelf);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

