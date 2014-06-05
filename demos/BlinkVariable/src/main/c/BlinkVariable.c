/**************************************************************************
 *
 * Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
 *
 *
 * Blinks with period adjustable through ADC.
 *
 **************************************************************************/

#include <stdbool.h>
#include <stddef.h>

#include <avr/io.h>

#include <avrtk/adc/CallbackAdcListener.h>
#include <avrtk/tasks/CallbackTask.h>

#include <avrtk/sys/SysAdcService.h>
#include <avrtk/sys/SysEventManager.h>
#include <avrtk/sys/SysTaskService.h>
#include <avrtk/sys/atm328p/Atm328pAdcService.h>
#include <avrtk/sys/atm328p/Atm328pTaskService.h>



static const long MIN_DELAY      = 250L;
static const long MAX_DELAY      = 2000L;
static const int  ADC_CHANNEL_ID = 0;

static void blinkCallback(void);
static void adcCallback(AdcSample *sample);

static TaskService *_taskService = NULL;
static Task        *_blinkTask   = NULL;
static long         _blinkDelay  = 500L;
static bool         _isLedOn     = true;






/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int main(void) {

    Atm328pTaskService_init();
    Atm328pAdcService_init();

    /* Set pin 5 of PORTD for output*/
    DDRD |= _BV(DDD5);


    CallbackTask  callbackTaskData;
    CallbackTask *callbackTask =
        CallbackTask_init(&callbackTaskData, &blinkCallback);
    Task         *task         = CallbackTask_asTask(callbackTask);
    TaskService  *taskService  = SysTaskService_get();
    
    TaskService_addTask(taskService, task, 0L);


    AdcService          *adcService = SysAdcService_get();
    AdcChannel           adcChannelData;
    AdcChannel          *adcChannel =
        AdcService_initChannel(adcService, &adcChannelData, ADC_CHANNEL_ID);
    CallbackAdcListener  callbackAdcListenerData;
    CallbackAdcListener *callbackAdcListener =
        CallbackAdcListener_init(&callbackAdcListenerData, &adcCallback);
    AdcListener         *adcListener =
        CallbackAdcListener_asAdcListener(callbackAdcListener);

    AdcChannel_addListener(adcChannel, adcListener);

    _taskService = taskService;
    _blinkTask   = task;

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

    TaskService_addTask(_taskService, _blinkTask, _blinkDelay);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void adcCallback(AdcSample *sample) {

    long value    = AdcSample_getValue(sample);
    long newDelay = MIN_DELAY + (MAX_DELAY-MIN_DELAY)*value / 0xffff;

    _blinkDelay = newDelay;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

