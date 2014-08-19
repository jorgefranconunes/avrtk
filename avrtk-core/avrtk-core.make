# -*- mode: makefile-gmake; -*-
###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

AVRTK_CORE_C_SOURCES = 

AVRTK_CORE_C_SOURCES += \
	avrtk/adc/AdcChannel.c \
	avrtk/adc/AdcEvent.c \
	avrtk/adc/AdcEventType.c \
	avrtk/adc/AdcListener.c \
	avrtk/adc/AdcSample.c \
	avrtk/adc/AdcService.c \
	avrtk/adc/AdcSource.c \
	avrtk/adc/AdcSourceChannel.c \
	avrtk/adc/BasicAdcSource.c \
	avrtk/adc/CallbackAdcListener.c

AVRTK_CORE_C_SOURCES += \
	avrtk/buttons/ButtonChannel.c \
	avrtk/buttons/ButtonListener.c

AVRTK_CORE_C_SOURCES += \
	avrtk/events/Event.c \
	avrtk/events/EventListener.c \
	avrtk/events/EventManager.c \
	avrtk/events/EventSource.c \
	avrtk/events/EventType.c

AVRTK_CORE_C_SOURCES += \
	avrtk/sys/SysAdcService.c \
	avrtk/sys/SysEventManager.c \
	avrtk/sys/SysTaskService.c \
	avrtk/sys/SysTickSource.c

AVRTK_CORE_C_SOURCES += \
	avrtk/tasks/CallbackTask.c \
	avrtk/tasks/Task.c \
	avrtk/tasks/TaskScheduler.c \
	avrtk/tasks/TaskService.c \

AVRTK_CORE_C_SOURCES += \
	avrtk/ticks/Clock.c \
	avrtk/ticks/CounterClock.c \
	avrtk/ticks/CounterTickSource.c \
	avrtk/ticks/TickEventType.c

