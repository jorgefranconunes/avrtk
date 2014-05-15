###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

B_PROJ_ROOT = ..

include $(B_PROJ_ROOT)/make/avrtk.make


B_PROJ = avrtk-test

B_CC_FLAGS = -g -Os -Wall -std=gnu99


#
# The core library, to be compiled with the host GCC.
#

B_MAIN_C_SRCDIR = $(B_PROJ_ROOT)/avrtk-core/src/main/c

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


#
# Unit tests, to be run on the host.
#

B_TEST_CXX_FLAGS = \
	-g \
	-I $(CPPUTEST)/include

B_TEST_LD_FLAGS = \
	-L $(CPPUTEST)/lib \
	-lCppUTest

B_TEST_C_SOURCES = \
	avrtk/events/TestEventListener.c \
	avrtk/events/TestEventSource.c \
	avrtk/tasks/TestClock.c \
	avrtk/tasks/TestTask.c

B_TEST_CXX_SOURCES = \
	AllTests.cpp \
	avrtk/events/EventManagerTest.cpp \
	avrtk/sys/SysTaskServiceTest.cpp \
	avrtk/sys/SysTickSourceTest.cpp \
	avrtk/tasks/CallbackTaskTest.cpp \
	avrtk/tasks/TaskSchedulerTest.cpp \
	avrtk/tasks/TaskServiceTest.cpp \
	avrtk/ticks/CounterClockTest.cpp \
	avrtk/ticks/CounterTickSourceTest.cpp \
	avrtk/ticks/TickEventTypeTest.cpp


include $(B_PROJ_ROOT)/make/lib.make

