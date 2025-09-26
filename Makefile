# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Source and object files
SRC = src/main.c src/control_transfer.c src/keymap.c src/light_modes.c src/keyboard.c
OBJ = $(SRC:.c=.o)

# Output binary
TARGET = nuphy_linux

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -lusb-1.0 -o $@

# Compiling
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean