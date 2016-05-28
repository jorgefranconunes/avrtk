/**************************************************************************
 *
 * Copyright (c) 2014-2016 Jorge Nunes, All Rights Reserved.
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


static const int  ADC_CHANNEL_ID = 0;
static const long MIN_DELAY      = 100L;
static const long MAX_DELAY      = 500L;


static void setupBlinkTask(void);
static void setupAdcListener(void);
static void blinkCallback(void);
static void adcCallback(AdcSample *sample);


static CallbackTask        _callbackTaskData;
static AdcChannel          _adcChannelData;
static CallbackAdcListener _callbackAdcListenerData;

static TaskService *_taskService = NULL;
static Task        *_blinkTask   = NULL;
static long         _blinkDelay  = 500L;
static bool         _isLedOn     = true;


/**
 *
 */
int main() {

    Atm328pTaskService_init();
    Atm328pAdcService_init();

    /* Set pin 5 of PORTD for output*/
    DDRD |= _BV(DDD5);

    setupBlinkTask();
    setupAdcListener();

    /* Run forever. */
    SysEventManager_start();
}


/**
 *
 */
static void setupBlinkTask() {

    CallbackTask *callbackTask =
        CallbackTask_init(&_callbackTaskData, &blinkCallback);
    Task         *blinkTask    = CallbackTask_asTask(callbackTask);
    TaskService  *taskService  = SysTaskService_get();

    TaskService_addTask(taskService, blinkTask, 0L);

    _taskService = taskService;
    _blinkTask   = blinkTask;
}


/**
 *
 */
static void setupAdcListener() {

    AdcService *adcService = SysAdcService_get();
    AdcChannel *adcChannel =
        AdcService_initChannel(adcService, &_adcChannelData, ADC_CHANNEL_ID);

    CallbackAdcListener *callbackAdcListener =
        CallbackAdcListener_init(&_callbackAdcListenerData, &adcCallback);
    AdcListener         *adcListener         =
        CallbackAdcListener_asAdcListener(callbackAdcListener);

    AdcChannel_addListener(adcChannel, adcListener);
}


/**
 * Called periodically by the task service. Toggles the LED connected
 * to port 5.
 */
static void blinkCallback() {

    if ( _isLedOn ) {
        PORTD |= _BV(PORTD5);
    } else {
        PORTD &= ~_BV(PORTD5);
    }

    _isLedOn = !_isLedOn;

    TaskService_addTask(_taskService, _blinkTask, _blinkDelay);
}


/**
 * Called when an ADC measurment is finished.
 */
static void adcCallback(AdcSample *sample) {

    long value    = AdcSample_getValue(sample);
    long newDelay = MIN_DELAY + (MAX_DELAY-MIN_DELAY)*value / 0xffff;

    _blinkDelay = newDelay;
}
