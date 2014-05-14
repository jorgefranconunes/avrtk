###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

B_PROJ_VERSION = 0.0.2

MODULES = \
	avrtk-core \
	avrtk-test \
	avrtk-atm328p \
	demos/Blink \
	demos/Blink101 \
	demos/BlinkMany \
	demos/HelloWorld



.PHONY : default all check clean

default : all

all : Makefile.conf
	@for module in $(MODULES) ; do make -C $$module $@ || exit 1; done

check : Makefile.conf
	@for module in $(MODULES) ; do make -C $$module $@ || exit 1; done

clean : Makefile.conf
	@for module in $(MODULES) ; do make -C $$module $@ || exit 1; done





-include Makefile.conf

Makefile.conf : 
	@echo "***"
	@echo "*** File \"Makefile.conf\" is missing."
	@echo "*** See 00README-developers.txt for aditional details."
	@echo "***"
	@exit 1

