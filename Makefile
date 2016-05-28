###########################################################################
#
# Copyright (c) 2014-2016 Jorge Nunes, All Rights Reserved.
#
###########################################################################

MODULES = \
	avrtk-test \
	avrtk-atm328p \
	demos/001-HelloWorld \
	demos/002-Blink101 \
	demos/003-Blink \
	demos/004-BlinkMany \
	demos/005-BlinkVariable101 \
	demos/006-BlinkVariable \
	demos/007-BlinkManyVariable \
	demos/008-AdcGauge101 \
	demos/009-AdcGauge \



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

