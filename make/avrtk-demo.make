# -*- mode: makefile-gmake; -*-
###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
#
# Makefile rules for building one of the demo apps bundled with avrtk.
#
###########################################################################

ifdef DEMO_AVRTK_ARCH
AVRATK_ARCH = $(DEMO_AVRATK_ARCH)
else
AVRTK_ARCH = atmega328p
endif

DEMO_BASENAME = $(B_PROJ)-$(B_PROJ_VERSION)-$(AVRTK_ARCH).hex
DEMO_TARGET   = $(B_PROJ_ROOT)/bin/$(DEMO_BASENAME)

B_MAIN_CC_FLAGS +=  \
	-I $(B_PROJ_ROOT)/avrtk-core/src/main/c \
	-I $(B_PROJ_ROOT)/avrtk-atm328p/src/main/c

B_MAIN_LD_FLAGS += \
	-L $(B_PROJ_ROOT)/lib \
	-lavrtk-$(B_PROJ_VERSION)-$(AVRTK_ARCH)



include $(B_PROJ_ROOT)/make/app.make


all :: $(DEMO_TARGET)

clean ::
	$(B_DELETE) $(DEMO_TARGET)

$(DEMO_TARGET) : $(B_MAIN_TARGET)
	avr-objcopy -O ihex -R .eeprom $< $@





###########################################################################
#
# 
#
###########################################################################

