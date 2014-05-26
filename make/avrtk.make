# -*- mode: makefile-gmake; -*-
###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
#
# The following variables must be defined:
#
# AVRTK_ARCH - The target MCU type to be used by the compiler. This
# value must be one of the allowed values for the -mmcu option of
# avr-gcc.
#
###########################################################################

B_PROJ_VERSION = 0.0.2

include $(B_PROJ_ROOT)/make/defs.make
include $(B_PROJ_ROOT)/Makefile.conf


#
# Use the avr-gcc cross compiler by default.
#
B_CC       = avr-gcc
B_CC_FLAGS = -g -Os -Wall -std=gnu99 -mmcu=$(AVRTK_ARCH) -DNDEBUG

B_LD       = avr-gcc
B_LD_FLAGS = -mmcu=$(AVRTK_ARCH)

B_AR     = avr-ar
B_RANLIB = avr-ranlib





###########################################################################
#
# 
#
###########################################################################

