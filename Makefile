# SRCS = \
#     dispatch_apply.c \
#     dispatch_group.c \
#     dispatch_queue.c \
#     dispatch_semaphore.c \
#     dispatch_source_timer.c

# OBJS = $(subst .c,.o,$(SRCS))

CFLAGS = 
LIBS =

SRCDIR := src
BUILDDIR := build
TARGETDIR := bin

SRCEXT := c
SRCS := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SRCS:.$(SRCEXT)=.o))

# TARGETWITHDIR := $(patsubst $(SRCDIR)/%,$(TARGETDIR)/%,$(SRCS:.$(SRCEXT)=))
TARGET := $(patsubst $(SRCDIR)/%,%,$(SRCS:.$(SRCEXT)=))

all: $(TARGET)

$(TARGET): $(OBJS)
		@mkdir -p $(TARGETDIR)
		clang -o $(TARGETDIR)/$@ $(BUILDDIR)/$@.o $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
		@mkdir -p $(BUILDDIR)
		clang -c $(CFLAGS) -I. $< -o $@

clean:
		rm -rf $(BUILDDIR)/ $(TARGETDIR)/

debug:
		@echo $(OBJS)

.PHONY: clean
