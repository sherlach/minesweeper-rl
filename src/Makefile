CC = gcc 
CC = clang
CFLAGS = -Wall -g #-O2 #-fno-strength-reduce -pipe -D"USE_GCU"
LIBS = -lncurses -ltinfo
#LDFLAGS = -s
#DEBUG = -g

SRCS = display.c main.c 

OBJS = display.o main.o 

#gcc -O2 -ltinfo -lncurses main.c

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
