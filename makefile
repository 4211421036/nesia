CC = gcc
CFLAGS = -Iinclude -I/usr/include/SDL2 -std=c11 -Wall
LDFLAGS = $(shell sdl2-config --libs)
SRC_DIR = src
BIN_DIR = bin
OBJS = $(SRC_DIR)/ast.o $(SRC_DIR)/lexer.o $(SRC_DIR)/parser.o \
       $(SRC_DIR)/interpreter.o $(SRC_DIR)/error.o

all: dirs nesia-cli nesia-gui

dirs:
    mkdir -p $(BIN_DIR)

nesia-cli: $(OBJS) $(SRC_DIR)/cli.o $(SRC_DIR)/main.o
    $(CC) $(CFLAGS) -o $(BIN_DIR)/nesia-cli $^ $(LDFLAGS)

nesia-gui: $(OBJS) $(SRC_DIR)/gui.o
    $(CC) $(CFLAGS) -o $(BIN_DIR)/nesia-gui $^ $(LDFLAGS)

clean:
    rm -rf $(BIN_DIR) $(SRC_DIR)/*.o

.PHONY: all dirs clean
