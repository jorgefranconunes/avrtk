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

B_MAIN_TARGET_BASENAME = lib$(B_PROJ)-$(B_PROJ_VERSION).a
B_MAIN_TARGET          = $(B_TARGET_DIR)/$(B_MAIN_TARGET_BASENAME)

B_TEST_TARGET = $(B_TARGET_DIR)/AllTests





.PHONY : default all check clean

default : all

all : $(B_MAIN_TARGET)

#
# The "check" target only builds the unit test runner if there are
# actually test source files.
#
ifneq (,$(B_TEST_C_SOURCES)$(B_TEST_CXX_SOURCES))
check : $(B_TEST_TARGET)
	$(B_TEST_TARGET)
else
check : $(B_MAIN_TARGET)
endif

clean :
	$(B_DELETE) $(B_TARGET_DIR)





###########################################################################
#
# Rules for compiling the main source code and creating the library
# archive.
#
###########################################################################

B_MAIN_ALL_OBJDIR = $(B_TARGET_DIR)/main_o

B_MAIN_C_OBJDIR   = $(B_MAIN_ALL_OBJDIR)
B_MAIN_CXX_OBJDIR = $(B_MAIN_ALL_OBJDIR)

B_MAIN_C_OBJS   = $(B_MAIN_C_SOURCES:%.c=$(B_MAIN_C_OBJDIR)/%.o)
B_MAIN_CXX_OBJS = $(B_MAIN_CXX_SOURCES:%.cpp=$(B_MAIN_CXX_OBJDIR)/%.o)

B_MAIN_ALL_OBJS = $(B_MAIN_C_OBJS) $(B_MAIN_CXX_OBJS)
B_MAIN_ALL_DEPS = $(B_MAIN_ALL_OBJS:%.o=%.o.d)


B_MY_MAIN_CC_FLAGS = \
	-I $(B_MAIN_C_SRCDIR) \
	 $(B_MAIN_CC_FLAGS)

B_MY_MAIN_CXX_FLAGS = \
	-I $(B_MAIN_CXX_SRCDIR) \
	-I $(B_MAIN_C_SRCDIR) \
	$(B_MAIN_CXX_FLAGS) 


$(B_MAIN_TARGET) : $(B_MAIN_ALL_OBJS)
	$(B_AR) cru $(B_MAIN_TARGET) $(B_MAIN_ALL_OBJS)
	$(B_RANLIB) $(B_MAIN_TARGET)

$(B_MAIN_C_OBJDIR)/%.o : $(B_MAIN_C_SRCDIR)/%.c
	$(B_MKDIR) $(@D)
	$(B_MAIN_CC) -c $(B_MY_MAIN_CC_FLAGS) -MT $@ -MD -MP -MF $@.d -o $@ $<

$(B_MAIN_CXX_OBJDIR)/%.o : $(B_MAIN_CXX_SRCDIR)/%.cpp
	$(B_MKDIR) $(@D)
	$(B_MAIN_CXX) -c $(B_MY_MAIN_CXX_FLAGS) -MT $@ -MD -MP -MF $@.d -o $@ $<

# Include the generated dependencies for the main source files. But we
# do not worry if they do not exist yet.
-include $(B_MAIN_ALL_DEPS)





###########################################################################
#
# Rules for compiling the test source code and creating the unit tests
# runner application.
#
###########################################################################

B_TEST_ALL_OBJDIR = $(B_TARGET_DIR)/test_o

B_TEST_C_OBJDIR   = $(B_TEST_ALL_OBJDIR)
B_TEST_CXX_OBJDIR = $(B_TEST_ALL_OBJDIR)

B_TEST_C_OBJS   = $(B_TEST_C_SOURCES:%.c=$(B_TEST_C_OBJDIR)/%.o)
B_TEST_CXX_OBJS = $(B_TEST_CXX_SOURCES:%.cpp=$(B_TEST_CXX_OBJDIR)/%.o)

B_TEST_ALL_OBJS = $(B_TEST_C_OBJS) $(B_TEST_CXX_OBJS)
B_TEST_ALL_DEPS = $(B_TEST_ALL_OBJS:%.o=%.o.d)


B_MY_TEST_CC_FLAGS = \
	-I $(B_TEST_C_SRCDIR) \
	-I $(B_MAIN_C_SRCDIR) \
	 $(B_TEST_CC_FLAGS)

B_MY_TEST_CXX_FLAGS = \
	-I $(B_TEST_CXX_SRCDIR) \
	-I $(B_TEST_CXX_SRCDIR) \
	-I $(B_TEST_C_SRCDIR) \
	-I $(B_MAIN_C_SRCDIR) \
	 $(B_TEST_CXX_FLAGS)

B_MY_TEST_LD_FLAGS = \
	-L$(B_TARGET_DIR) \
	-l $(B_PROJ)-$(B_PROJ_VERSION) \
	$(B_TEST_LD_FLAGS)


$(B_TEST_TARGET) : $(B_MAIN_TARGET) $(B_TEST_ALL_OBJS)
	$(B_TEST_LD) -o $@ $(B_TEST_ALL_OBJS) $(B_MY_TEST_LD_FLAGS)

$(B_TEST_C_OBJDIR)/%.o : $(B_TEST_C_SRCDIR)/%.c
	$(B_MKDIR) $(@D)
	$(B_TEST_CC) -c $(B_MY_TEST_CC_FLAGS) -MT $@ -MD -MP -MF $@.d -o $@ $<

$(B_TEST_CXX_OBJDIR)/%.o : $(B_TEST_CXX_SRCDIR)/%.cpp
	$(B_MKDIR) $(@D)
	$(B_TEST_CXX) -c $(B_MY_TEST_CXX_FLAGS) -MT $@ -MD -MP -MF $@.d -o $@ $<

# Include the generated dependencies for the test source files. But we
# do not worry if they do not exist yet.
-include $(B_TEST_ALL_DEPS)





###########################################################################
#
# 
#
###########################################################################

