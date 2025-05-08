CC = gcc
CFLAGS = -Iinclude -I/usr/include/SDL2 -std=c11 -Wall
LDFLAGS = $(shell sdl2-config --libs)
SRCS = src/*.c
OBJS = $(SRCS:.c=.o)

all: nesia nesia-gui

nesia: $(OBJS)
	$(CC) $(CFLAGS) -o bin/nesia $(OBJS) $(LDFLAGS)

nesia-gui: $(OBJS)
	$(CC) $(CFLAGS) -o bin/nesia-gui $(OBJS) $(LDFLAGS)

clean:
	rm -f src/*.o bin/nesia bin/nesia-gui
