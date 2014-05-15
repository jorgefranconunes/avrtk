###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

B_PROJ_ROOT = ..

include $(B_PROJ_ROOT)/make/avrtk.make


B_PROJ = avrtk-core

B_CC       = avr-gcc
B_CC_FLAGS = -g -Os -Wall -std=gnu99 -mmcu=atmega328p -DNDEBUG

B_LD     = avr-gcc
B_AR     = avr-ar
B_RANLIB = avr-ranlib


#
# The main sources, to be compiled with AVR-GCC.
#

B_MAIN_C_SOURCES = \
	avrtk/events/Event.c \
	avrtk/events/EventListener.c \
	avrtk/events/EventManager.c \
	avrtk/events/EventSource.c \
	avrtk/events/EventType.c \
	avrtk/sys/SysEventManager.c \
	avrtk/sys/SysTaskService.c \
	avrtk/sys/SysTickSource.c \
	avrtk/tasks/CallbackTask.c \
	avrtk/tasks/CounterTaskService.c \
	avrtk/tasks/Task.c \
	avrtk/tasks/TaskScheduler.c \
	avrtk/tasks/TaskService.c \
	avrtk/ticks/Clock.c \
	avrtk/ticks/CounterClock.c \
	avrtk/ticks/CounterTickSource.c \
	avrtk/ticks/TickEventType.c


include ../make/lib.make

