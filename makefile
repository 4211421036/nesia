CC = gcc
CFLAGS = -Iinclude $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

SRCS = src/ast.c src/cli.c src/error.c src/gui.c src/interpreter.c \
       src/lexer.c src/main.c src/parser.c
OBJS = $(SRCS:.c=.o)

all: nesia nesia-gui

nesia: $(OBJS)
	$(CC) -o bin/nesia $(SRCS) $(LDFLAGS)

nesia-gui: $(OBJS)
	$(CC) -o bin/nesia-gui $(SRCS) $(LDFLAGS)

clean:
	rm -f src/*.o bin/nesia bin/nesia-gui

.PHONY: all clean
