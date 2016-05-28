/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 **************************************************************************/

#include <stdbool.h>

#include <avr/io.h>

#include <avrtk/tasks/CallbackTask.h>

#include <avrtk/sys/SysEventManager.h>
#include <avrtk/sys/SysTaskService.h>
#include <avrtk/sys/atm328p/Atm328pTaskService.h>





#define BLINK_DELAY_MS 1000L

static void blinkCallback(void);

static bool _isLedOn = true;






/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int main(void) {

    Atm328pTaskService_init();

    /* Set pin 5 of PORTD for output*/
    DDRD |= _BV(DDD5);

    CallbackTask  callbackTaskData;
    CallbackTask *callbackTask =
        CallbackTask_init(&callbackTaskData, &blinkCallback);
    Task         *task         = CallbackTask_asTask(callbackTask);
    TaskService  *taskService  = SysTaskService_get();

    TaskService_addPeriodicTask(taskService, task, 0L, BLINK_DELAY_MS);

    /* Run forever. */
    SysEventManager_start();
}





/**************************************************************************
 *
 * Called once per 0.5s. Toggles the LED connected to port 5.
 *
 **************************************************************************/

static void blinkCallback() {

    if ( _isLedOn ) {
        PORTD |= _BV(PORTD5);
    } else {
        PORTD &= ~_BV(PORTD5);
    }

    _isLedOn = !_isLedOn;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

