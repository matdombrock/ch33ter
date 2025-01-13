# Compiler
CC = clang
CROSS_CC = x86_64-w64-mingw32-gcc

# Compiler flags
CFLAGS = -Wall -Werror -std=c99

# Source files
SRCS = ./src/main.c

# Output directory and executable
OUT_DIR = ./out
TARGET = $(OUT_DIR)/main.out
CROSS_TARGET = $(OUT_DIR)/main.exe

# Build target
all: $(TARGET)

$(TARGET): $(SRCS) | $(OUT_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

cross: $(CROSS_TARGET)

$(CROSS_TARGET): $(SRCS) | $(OUT_DIR)
	$(CROSS_CC) $(CFLAGS) -o $(CROSS_TARGET) $(SRCS)

init:
	mkdir -p $(OUT_DIR)

run: all
	$(TARGET)

# Clean target
clean:
	rm -f $(TARGET) $(CROSS_TARGET)

# Phony targets
.PHONY: all clean init run cross