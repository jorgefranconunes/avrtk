###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

B_PROJ_ROOT = ../..

include $(B_PROJ_ROOT)/make/avrtk.make


B_PROJ = HelloWorld


#
# The main sources, to be compiled with AVR-GCC.
#

B_MAIN_CC_FLAGS = \
	$(B_CC_FLAGS) \
	-DF_CPU=16000000UL

B_MAIN_C_SOURCES = \
	HelloWorld.c


include $(B_PROJ_ROOT)/make/avrtk-demo.make

