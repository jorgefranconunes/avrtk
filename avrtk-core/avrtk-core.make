# -*- mode: makefile-gmake; -*-
###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

AVRTK_CORE_C_SOURCES = \
	avrtk/adc/AdcEvent.c \
	avrtk/adc/AdcEventType.c \
	avrtk/adc/AdcSample.c \
	avrtk/events/Event.c \
	avrtk/events/EventListener.c \
	avrtk/events/EventManager.c \
	avrtk/events/EventSource.c \
	avrtk/events/EventType.c \
	avrtk/sys/SysEventManager.c \
	avrtk/sys/SysTaskService.c \
	avrtk/sys/SysTickSource.c \
	avrtk/tasks/CallbackTask.c \
	avrtk/tasks/Task.c \
	avrtk/tasks/TaskScheduler.c \
	avrtk/tasks/TaskService.c \
	avrtk/ticks/Clock.c \
	avrtk/ticks/CounterClock.c \
	avrtk/ticks/CounterTickSource.c \
	avrtk/ticks/TickEventType.c

