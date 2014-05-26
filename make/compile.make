# -*- mode: makefile-gmake; -*-
###########################################################################
#
# Copyright (c) 2014 Jorge Nunes, All Rights Reserved.
#
#
# The following variables must be defined:
#
# B_TARGET_DIR
# B_SOURCESET
# B_SOURCESET_C_SOURCES
# B_SOURCESET_C_SRCDIR
# B_SOURCESET_CC
# B_SOURCESET_CC_FLAGS
# B_SOURCESET_CXX_SOURCES
# B_SOURCESET_CXX_SRCDIR
# B_SOURCESET_CXX
# B_SOURCESET_CXX_FLAGS
#
###########################################################################





###########################################################################
#
# Rules for compiling the source set source code.
#
###########################################################################

B_$(B_SOURCESET)_ALL_OBJDIR := $(B_TARGET_DIR)/$(B_SOURCESET)_o

B_$(B_SOURCESET)_C_OBJDIR   := $(B_$(B_SOURCESET)_ALL_OBJDIR)
B_$(B_SOURCESET)_CXX_OBJDIR = $(B_$(B_SOURCESET)_ALL_OBJDIR)

B_$(B_SOURCESET)_C_OBJS   := $(B_$(B_SOURCESET)_C_SOURCES:%.c=$(B_$(B_SOURCESET)_C_OBJDIR)/%.o)
B_$(B_SOURCESET)_CXX_OBJS := $(B_$(B_SOURCESET)_CXX_SOURCES:%.cpp=$(B_$(B_SOURCESET)_CXX_OBJDIR)/%.o)

B_$(B_SOURCESET)_ALL_OBJS := $(B_$(B_SOURCESET)_C_OBJS) $(B_$(B_SOURCESET)_CXX_OBJS)
B_$(B_SOURCESET)_ALL_DEPS := $(B_$(B_SOURCESET)_ALL_OBJS:%.o=%.o.d)


B_MY_$(B_SOURCESET)_CC_FLAGS := \
	-I $(B_$(B_SOURCESET)_C_SRCDIR) \
	 $(B_$(B_SOURCESET)_CC_FLAGS)

B_MY_$(B_SOURCESET)_CXX_FLAGS := \
	-I $(B_$(B_SOURCESET)_CXX_SRCDIR) \
	-I $(B_$(B_SOURCESET)_C_SRCDIR) \
	$(B_$(B_SOURCESET)_CXX_FLAGS) 

$(B_$(B_SOURCESET)_C_OBJS) : B_SOURCESET_CC := $(B_$(B_SOURCESET)_CC)
$(B_$(B_SOURCESET)_C_OBJS) : B_MY_SOURCESET_CC_FLAGS := $(B_MY_$(B_SOURCESET)_CC_FLAGS)

$(B_$(B_SOURCESET)_C_OBJDIR)/%.o : $(B_$(B_SOURCESET)_C_SRCDIR)/%.c
	$(B_MKDIR) $(@D)
	$(B_SOURCESET_CC) -c $(B_MY_SOURCESET_CC_FLAGS) -MT $@ -MD -MP -MF $@.d -o $@ $<


$(B_$(B_SOURCESET)_CXX_OBJS) : B_SOURCESET_CXX := $(B_$(B_SOURCESET)_CXX)
$(B_$(B_SOURCESET)_CXX_OBJS) : B_MY_SOURCESET_CXX_FLAGS := $(B_MY_$(B_SOURCESET)_CXX_FLAGS)

$(B_$(B_SOURCESET)_CXX_OBJDIR)/%.o : $(B_$(B_SOURCESET)_CXX_SRCDIR)/%.cpp
	$(B_MKDIR) $(@D)
	$(B_SOURCESET_CXX) -c $(B_MY_SOURCESET_CXX_FLAGS) -MT $@ -MD -MP -MF $@.d -o $@ $<

# Include the generated dependencies for the source set source
# files. But we do not worry if they do not exist yet.
-include $(B_$(B_SOURCESET)_ALL_DEPS)





###########################################################################
#
# 
#
###########################################################################

