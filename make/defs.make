# -*- mode: makefile-gmake; -*-
###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################




#
# Defaults for directories and tools.
#

B_TARGET_DIR = target

B_CC = gcc
B_CC_FLAGS =

B_CXX = g++
B_CXX_FLAGS =

B_LD = g++
B_LD_FLAGS =

B_AR = ar 
B_RANLIB = ranlib

B_MKDIR = mkdir -p
B_DELETE = rm -rf


#
# Defaults for the "main" source set.
#

B_MAIN_C_SRCDIR = src/main/c
B_MAIN_CC = $(B_CC)
B_MAIN_CC_FLAGS = $(B_CC_FLAGS)

B_MAIN_CXX_SRCDIR = src/main/cpp
B_MAIN_CXX = $(B_CXX)
B_MAIN_CXX_FLAGS = $(B_CXX_FLAGS)

B_MAIN_LD = $(B_LD)
B_MAIN_LD_FLAGS = $(B_LD_FLAGS)


#
# Defaults for the "test" source set.
#

B_TEST_C_SRCDIR = src/test/c
B_TEST_CC = $(B_CC)
B_TEST_CC_FLAGS = $(B_CC_FLAGS)

B_TEST_CXX_SRCDIR = src/test/cpp
B_TEST_CXX = $(B_CXX)
B_TEST_CXX_FLAGS = $(B_CXX_FLAGS)

B_TEST_LD = $(B_LD)
B_TEST_LD_FLAGS = $(B_LD_FLAGS)





###########################################################################
#
# 
#
###########################################################################

