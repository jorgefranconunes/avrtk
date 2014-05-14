###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
###########################################################################

B_PROJ = dummy

B_PROJ_VERSION = 0.0.1





#
#
#
B_TARGET_DIR = target

B_MAIN_C_SRCDIR   = src/main/c
B_MAIN_CXX_SRCDIR = src/main/cpp

B_TEST_C_SRCDIR   = src/test/c
B_TEST_CXX_SRCDIR = src/test/cpp

B_CC = gcc
B_MAIN_CC = $(B_CC)
B_TEST_CC = $(B_CC)

B_CC_FLAGS =
B_MAIN_CC_FLAGS = $(B_CC_FLAGS)
B_TEST_CC_FLAGS = $(B_CC_FLAGS)

B_CXX = g++
B_MAIN_CXX = $(B_CXX)
B_TEST_CXX = $(B_CXX)

B_CXX_FLAGS =
B_MAIN_CXX_FLAGS = $(B_CXX_FLAGS)
B_TEST_CXX_FLAGS = $(B_CXX_FLAGS)

B_LD = g++
B_MAIN_LD = $(B_LD)
B_TEST_LD = $(B_LD)

B_LD_FLAGS =
B_MAIN_LD_FLAGS = $(B_LD_FLAGS)
B_TEST_LD_FLAGS = $(B_LD_FLAGS)

B_AR = ar 
B_RANLIB = ranlib





#
# Tools used during the build.
#
B_MKDIR = mkdir -p
B_DELETE = rm -rf





###########################################################################
#
# 
#
###########################################################################

