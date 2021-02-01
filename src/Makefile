CC = gcc 
CFLAGS = -Wall #-O2 #-fno-strength-reduce -pipe -D"USE_GCU"
LIBS = -lncurses -ltinfo
#LDFLAGS = -s
DEBUG = -ggdb

SRCS = display.c main.c 

OBJS = display.o main.o 

#gcc -O2 -ltinfo -lncurses main.c

# Default target
#
all: msweaper


# Install the game
#
install: msweaper
	cp msweaper ..

# Build the game
#
msweaper: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o msweaper $(DEBUG) $(OBJS) $(LIBS)

# Clean up before a fresh build
#
clean:
	-rm -fv *.o msweaper 


# Generate deps
#
depend:
	makedepend -D__MAKEDEPEND__ $(SRCS)
