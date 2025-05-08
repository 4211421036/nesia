# Direktori sumber dan biner
SRC_DIR = src
BIN_DIR = bin

# Compiler & flags
CC = gcc
CFLAGS = -Iinclude -I/usr/include/SDL2 -std=c11 -Wall
LDFLAGS = $(shell sdl2-config --libs)

# Daftar file sumber dan objek
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(SRC_DIR)/%.o,$(SRCS))

# Target default
all: dirs nesia nesia-gui

# Buat direktori bin jika belum ada
dirs:
	mkdir -p $(BIN_DIR)

# Kompilasi objek
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Link untuk CLI
nesia: $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/nesia $(OBJS) $(LDFLAGS)

# Link untuk GUI
nesia-gui: $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/nesia-gui $(OBJS) $(LDFLAGS)

# Bersihkan hasil build
clean:
	rm -rf $(SRC_DIR)/*.o $(BIN_DIR)/nesia $(BIN_DIR)/nesia-gui

.PHONY: all dirs clean
