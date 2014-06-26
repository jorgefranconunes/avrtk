###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

MODULES = \
	avrtk-test \
	avrtk-atm328p \
	demos/AdcGauge \
	demos/AdcGauge101 \
	demos/Blink \
	demos/BlinkVariable \
	demos/BlinkVariable101 \
	demos/Blink101 \
	demos/BlinkMany \
	demos/HelloWorld



.PHONY : default all check clean doc

default : all

all check clean : Makefile.conf
	@for module in $(MODULES) ; do $(MAKE) -C $$module $@ || exit 1; done

doc :
	doxygen ./make/doxygen.conf
	@echo
	@echo "API docs are now at ./doc/api/index.html"
	@echo





-include Makefile.conf

Makefile.conf : 
	@echo "***"
	@echo "*** File \"Makefile.conf\" is missing."
	@echo "*** See 00README-developers.txt for aditional details."
	@echo "***"
	@exit 1

