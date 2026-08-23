# Stuff that manages our progress I found online

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all
MAKEFLAGS += -s
%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else 
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo "`expr "   [\`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`%]"
endif

# Define our linker and compiler binary
CC := g++
LD := g++

# Flags for compiler and linker
CFLAGS := -O2 -g
LFLAGS := -lglbinding -lGL -lSDL3 -lSDL3_image

# Directories and target file
BINDIR := build
OBJDIR := build/obj
SRCDIR := src
TARGET := $(BINDIR)/gquake

# Gets list of our source files, source files without directories, and object files to compile to
SRCS := $(shell find $(SRCDIR) -name *.cpp)
SRCFILES := $(notdir $(SRCS))
OBJS := $(SRCFILES:%.cpp=$(OBJDIR)/%.o)

# Define where to look for our source file dependencies
SRCSUB := $(shell find $(SRCDIR) -type d)
vpath %.cpp $(SRCSUB)

# Rules
all: $(TARGET)
	@$(ECHO) All done

$(TARGET): $(OBJS) | $(BINDIR)
	@$(ECHO) Linking $@
	@$(LD) $(LFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@$(ECHO) Compiling $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) $(BINDIR):
	@mkdir -p $@

.PHONY: clean
clean: $(BINDIR)
	@rm -r $(BINDIR)
	@$(ECHO) Clean done

.PHONY: test
test: test/main.cpp
	g++ $^ -o $(BINDIR)/test

endif
