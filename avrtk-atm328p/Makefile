###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

B_PROJ_ROOT = ..

include $(B_PROJ_ROOT)/make/avrtk.make


B_PROJ = avrtk-atm328p

B_CC       = avr-gcc
B_CC_FLAGS = -g -Os -Wall -std=gnu99 -mmcu=atmega328p -DNDEBUG

B_LD     = avr-gcc
B_AR     = avr-ar
B_RANLIB = avr-ranlib


#
# The main sources, to be compiled with AVR-GCC.
#

B_MAIN_CC_FLAGS = \
	$(B_CC_FLAGS) \
	-I $(B_PROJ_ROOT)/avrtk-core/src/main/c

B_MAIN_C_SOURCES = \
	avrtk/sys/atm328p/Atm328pTaskService.c \
	avrtk/sys/atm328p/Atm328pTickSource.c


include $(B_PROJ_ROOT)/make/lib.make

