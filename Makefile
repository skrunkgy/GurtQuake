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

# Define our linker and compiler
CC := g++
LD := g++

CFLAGS := -O2
LFLAGS := -lglbinding -lGL -lSDL3 -lSDL3_image

BINDIR := build
OBJDIR := build/obj
SRCDIR := src
TARGET := $(BINDIR)/gquake

SRCS := $(shell find $(SRCDIR) -name *.cpp)
SRCFILES := $(notdir $(SRCS))
OBJS := $(SRCFILES:%.cpp=$(OBJDIR)/%.o)

SRCSUB := $(shell find $(SRCDIR) -type d)
vpath %.cpp $(SRCSUB)

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

endif
