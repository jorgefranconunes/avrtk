# -*- mode: makefile-gmake; -*-
###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
#
# The following variables must be defined:
#
# B_PROJ
#
# B_PROJ_VERSION
#
# B_TARGET_DIR
#
# B_MAIN_C_SRCDIR
#
# B_MAIN_CXX_SRCDIR
#
# B_TEST_C_SRCDIR
#
# B_TEST_CXX_SRCDIR
#
#
# Many more variables can be defined by the Makefile that includes
# this file. See the commens on defs.make for an explanation of the
# variables that can be defined to override defaults.
#
###########################################################################

B_MAIN_TARGET_BASENAME = $(B_PROJ)-$(B_PROJ_VERSION)
B_MAIN_TARGET          = $(B_TARGET_DIR)/$(B_MAIN_TARGET_BASENAME)

B_TEST_TARGET = $(B_TARGET_DIR)/AllTests





.PHONY : default all check clean

default : all

all :: $(B_MAIN_TARGET)

#
# The "check" target only builds the unit test runner if there are
# actually test source files.
#
ifneq (,$(B_TEST_C_SOURCES)$(B_TEST_CXX_SOURCES))
check :: $(B_TEST_TARGET)
	$(B_TEST_TARGET)
else
check :: all
endif

clean ::
	$(B_DELETE) $(B_TARGET_DIR)





###########################################################################
#
# Rules for compiling the main source code and creating the library
# archive.
#
###########################################################################

B_SOURCESET := MAIN

include $(B_PROJ_ROOT)/make/compile.make


$(B_MAIN_TARGET) : $(B_MAIN_ALL_OBJS)
	$(B_MAIN_LD) -o $@ $(B_MAIN_ALL_OBJS) $(B_MAIN_LD_FLAGS)





###########################################################################
#
# Rules for compiling the test source code and creating the unit tests
# runner application.
#
###########################################################################

B_SOURCESET := TEST

B_TEST_CC_FLAGS := \
	-I $(B_TEST_C_SRCDIR) \
	-I $(B_MAIN_C_SRCDIR) \
	 $(B_TEST_CC_FLAGS)

B_TEST_CXX_FLAGS := \
	-I $(B_TEST_CXX_SRCDIR) \
	-I $(B_MAIN_CXX_SRCDIR) \
	-I $(B_TEST_C_SRCDIR) \
	-I $(B_MAIN_C_SRCDIR) \
	 $(B_TEST_CXX_FLAGS)

include $(B_PROJ_ROOT)/make/compile.make


B_MY_TEST_LD_FLAGS = \
	-L$(B_TARGET_DIR) \
	-l $(B_PROJ)-$(B_PROJ_VERSION) \
	$(B_TEST_LD_FLAGS)


$(B_TEST_TARGET) : all $(B_TEST_ALL_OBJS) $(B_MAIN_ALL_OBJS)
	$(B_TEST_LD) -o $@ $(B_TEST_ALL_OBJS) $(B_MY_TEST_LD_FLAGS)





###########################################################################
#
# 
#
###########################################################################

