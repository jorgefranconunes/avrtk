/**************************************************************************
 *
 * Copyright (c) 2015 Jorge Nunes, All Rights Reserved.
 *
 *
 * Blinks a set of 6 LEDs with frequency adjustable through ADC.
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





#define ADC_CHANNEL_ID 0

#define DELAY_DEFAULT 100L
#define DELAY_MIN     20L
#define DELAY_MAX     200L

static void setupAdcListener();
static void adcCallback(AdcSample *sample);
static void blinkCallback();
static void doBlink();

// The set of bit patterns to display in the set of LEDs.
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
static int  _patternCount = sizeof(_patterns) / sizeof(uint8_t);
static int  _patternMask  = 0b11111100;
static int  _patternIndex = 0;
static long _delay        = DELAY_DEFAULT;

static AdcChannel          _adcChannelData;
static CallbackAdcListener _callbackAdcListenerData;

static TaskService* _taskService;
static CallbackTask _blinkTaskData;
static Task*        _blinkTask;





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

int main(void) {

    Atm328pAdcService_init();
    Atm328pTaskService_init();

    /* Set the appropriate pins of PORTD for output*/
    DDRD |= _patternMask;

    setupAdcListener();

    CallbackTask* blinkTask =
        CallbackTask_init(&_blinkTaskData, &blinkCallback);

    _blinkTask   = CallbackTask_asTask(blinkTask);
    _taskService = SysTaskService_get();

    // Start the task that does the blinking.
    blinkCallback();

    /* Run forever. */
    SysEventManager_start();
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

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





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void adcCallback(AdcSample *sample) {

    uint32_t sampleValue = (uint32_t)AdcSample_getValue(sample);

    long delay = DELAY_MIN + (sampleValue*(DELAY_MAX-DELAY_MIN) / 0xffff);

    _delay = delay;
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void blinkCallback() {

    doBlink();

    TaskService_addTask(_taskService, _blinkTask, _delay);
}





/**************************************************************************
 *
 * 
 *
 **************************************************************************/

static void doBlink() {

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

