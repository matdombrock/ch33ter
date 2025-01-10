# Compiler
CC = clang

# Compiler flags
CFLAGS = -Wall -Werror -std=c99

# Source files
SRCS = ./src/main.c

# Output directory and executable
OUT_DIR = ./out
TARGET = $(OUT_DIR)/main.out

# Build target
all: $(TARGET)

$(TARGET): $(SRCS) | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

init:
	mkdir -p $(OUT_DIR)

run: all
	$(TARGET)

# Clean target
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean init run