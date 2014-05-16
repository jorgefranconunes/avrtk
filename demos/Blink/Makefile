###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

B_PROJ_ROOT = ../..

include $(B_PROJ_ROOT)/make/avrtk.make


B_PROJ = Blink

B_CC       = avr-gcc
B_CC_FLAGS = -g -Os -Wall -std=gnu99 -mmcu=atmega328p

B_LD       = avr-gcc
B_LD_FLAGS = -mmcu=atmega328p

B_AR     = avr-ar
B_RANLIB = avr-ranlib


#
# The main sources, to be compiled with AVR-GCC.
#

B_MAIN_CC_FLAGS = \
	$(B_CC_FLAGS) \
	-I $(B_PROJ_ROOT)/avrtk-core/src/main/c \
	-I $(B_PROJ_ROOT)/avrtk-atm328p/src/main/c

B_MAIN_LD_FLAGS = \
	$(B_LD_FLAGS) \
	-L $(B_PROJ_ROOT)/avrtk-atm328p/target \
	-lavrtk-atm328p-$(B_PROJ_VERSION) \
	-L $(B_PROJ_ROOT)/avrtk-core-atm328p/target \
	-lavrtk-core-$(B_PROJ_VERSION)

B_MAIN_C_SOURCES = \
	Blink.c


include $(B_PROJ_ROOT)/make/app.make 


all : $(B_PROJ_ROOT)/bin/$(B_PROJ).hex

$(B_PROJ_ROOT)/bin/$(B_PROJ).hex : $(B_MAIN_TARGET)
	avr-objcopy -O ihex -R .eeprom $< $@

