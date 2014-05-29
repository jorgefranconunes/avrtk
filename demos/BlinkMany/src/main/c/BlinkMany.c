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





#define DELAY_MS 100L

static void blinkCallback(void);

static uint8_t _patterns[] = {
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,

    0b11000000,
    0b11100000,
    0b11110000,
    0b11111000,
    0b11111100,
    0b11111000,
    0b11110000,
    0b11100000,
    0b11000000,
};
static int _patternCount = sizeof(_patterns) / sizeof(uint8_t);
static int _patternMask  = 0b11111100;
static int _patternIndex = 0;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int main(void) {

    Atm328pTaskService_init();

    /* Set the appropriate pins of PORTD for output*/
    DDRD |= _patternMask;

    CallbackTask  callbackTaskData;
    CallbackTask *callbackTask =
        CallbackTask_init(&callbackTaskData, &blinkCallback);
    Task         *task         = CallbackTask_asTask(callbackTask);
    TaskService  *taskService  = SysTaskService_get();
    
    TaskService_addPeriodicTask(taskService, task, 0L, DELAY_MS);

    /* Run forever. */
    SysEventManager_start();
}





/**************************************************************************
 *
 * Called once per 0.5s. Toggles the LED connected to port 5.
 *
 **************************************************************************/

static void blinkCallback() {

    PORTD =
        (_patterns[_patternIndex] & _patternMask)
        | (PORTD & ~_patternMask);

    ++_patternIndex;
    if ( _patternIndex == _patternCount ) {
        _patternIndex = 0;
    }
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

