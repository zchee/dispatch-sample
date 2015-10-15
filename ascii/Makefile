SRCS = \
    dispatch_async.c \
		dispatch_group_async.c

OBJS = $(subst .c,.o,$(SRCS))

CFLAGS = 
LIBS = 
TARGET = dispatch_async dispatch_group_async

all : $(TARGET)

$(TARGET) : $(OBJS)
		clang -o bin/$@ $@.o $(LIBS)

%.o : %.c
		clang -c $(CFLAGS) -I. $< -o $@

clean :
		rm -f *.o bin/$(TARGET)
