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

$(TARGET): $(OBJS) | $(BINDIR)
	$(LD) $(LFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR) $(BINDIR):
	mkdir -p $@

.PHONY: clean
clean: $(BINDIR)
	rm -r $(BINDIR)
