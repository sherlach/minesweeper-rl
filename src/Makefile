#CC = gcc
CC = clang
CFLAGS = -Wall -g #-O2 #-fno-strength-reduce -pipe -D"USE_GCU"
LIBS = -lncurses -ltinfo
#LDFLAGS = -s

SRCS = display.c main.c map.c player.c

OBJS = display.o main.o map.o player.o

# Default target
#
all: msweaper


# Install the game
#
install: msweaper
	mv msweaper ..

# Build the game
#
msweaper: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o msweaper $(OBJS) $(LIBS)

# Clean up before a fresh build
#
clean:
	-rm -fv *.o 


# Generate deps
#
#depend:
#	makedepend -D__MAKEDEPEND__ $(SRCS)
