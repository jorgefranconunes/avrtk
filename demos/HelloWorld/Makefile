###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

include ../../make/defs.make


B_PROJ = HelloWorld

B_CC       = avr-gcc
B_CC_FLAGS = -g -Os -Wall -std=gnu99 -mmcu=atmega328p

B_LD     = avr-gcc
B_LD_FLAGS = -mmcu=atmega328p

B_AR     = avr-ar
B_RANLIB = avr-ranlib


#
# The main sources, to be compiled with AVR-GCC.
#

B_MAIN_CC_FLAGS = \
	$(B_CC_FLAGS) \
	-DF_CPU=16000000UL

B_MAIN_C_SOURCES = \
	HelloWorld.c


include ../../make/app.make


all : ../../bin/$(B_PROJ).hex

../../bin/$(B_PROJ).hex : $(B_MAIN_TARGET)
	avr-objcopy -O ihex -R .eeprom $< $@

