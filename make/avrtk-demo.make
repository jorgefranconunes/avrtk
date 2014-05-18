# -*- mode: makefile-gmake; -*-
###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
#
# Makefile rules for building one of the demo apps bundled with avrtk.
#
###########################################################################

DEMO_BASENAME = $(B_PROJ)-$(B_PROJ_VERSION)-$(AVRTK_ARCH).hex
DEMO_TARGET   = $(B_PROJ_ROOT)/bin/$(DEMO_BASENAME)



include $(B_PROJ_ROOT)/make/app.make


all : $(DEMO_TARGET)

clean ::
	$(B_DELETE) $(DEMO_TARGET)

$(DEMO_TARGET) : $(B_MAIN_TARGET)
	avr-objcopy -O ihex -R .eeprom $< $@





###########################################################################
#
# 
#
###########################################################################

