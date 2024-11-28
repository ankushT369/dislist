# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# The target executable
TARGET = server

# Source files
SRCS = node_manager.c

# Object files (in the build directory)
OBJS = $(SRCS:%.c=build/%.o)

# Build directory
BUILD_DIR = build

# Default target to build and run the executable
all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)
	@echo "Running the executable..."
	@./$(BUILD_DIR)/$(TARGET)

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link object files to create the executable in the build directory
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c files into .o files in the build directory
build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets to avoid conflicts with file names
.PHONY: all clean
