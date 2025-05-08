# Direktori sumber dan biner
SRC_DIR = src
BIN_DIR = bin

# Compiler & flags
CC = gcc
CFLAGS = -Iinclude -I/usr/include/SDL2 -std=c11 -Wall
LDFLAGS = $(shell sdl2-config --libs)

# Daftar file sumber dan objek
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRC_DIR)/ast.o $(SRC_DIR)/lexer.o $(SRC_DIR)/parser.o \
       $(SRC_DIR)/interpreter.o $(SRC_DIR)/error.o

# Target default
all: dirs nesia-cli nesia-gui

# Buat direktori bin jika belum ada
dirs:
	mkdir -p $(BIN_DIR)

# Kompilasi objek
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Link untuk CLI
nesia-cli: $(OBJS) $(SRC_DIR)/cli.o $(SRC_DIR)/main.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/nesia-cli $^ $(LDFLAGS)

# Link untuk GUI
nesia-gui: $(OBJS) $(SRC_DIR)/gui.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/nesia-gui $^ $(LDFLAGS)

# Bersihkan hasil build
clean:
	rm -rf $(BIN_DIR) $(SRC_DIR)/*.o

.PHONY: all dirs clean
