# Compiler
CC = gcc
CROSS_CC = x86_64-w64-mingw32-gcc
LINUX_CC = x86_64-linux-musl-gcc

# Compiler flags
CFLAGS = -Wall -Werror -std=c99

# Source files
SRCS = ./src/main.c

# Output directory and executable
OUT_DIR = ./out
TARGET = $(OUT_DIR)/macOS/ch33ter
WIN_CROSS_TARGET = $(OUT_DIR)/win32/ch33ter.exe
LIN_CROSS_TARGET = $(OUT_DIR)/linux/ch33ter

# Build target
all: $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p $(OUT_DIR)/macOS
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

cross-win: $(WIN_CROSS_TARGET)

$(WIN_CROSS_TARGET): $(SRCS)
	mkdir -p $(OUT_DIR)/win32
	$(CROSS_CC) $(CFLAGS) -o $(WIN_CROSS_TARGET) $(SRCS)

cross-lin: $(LIN_CROSS_TARGET)

$(LIN_CROSS_TARGET): $(SRCS)
	mkdir -p $(OUT_DIR)/linux
	$(LINUX_CC) $(CFLAGS) -o $(LIN_CROSS_TARGET) $(SRCS)

# Dependency setup
deps-mac:
	xcode-select --install

deps-linux:
	sudo apt update && sudo apt install -y build-essential

package: all cross-win cross-lin
	cp README.MD $(OUT_DIR) && cd $(OUT_DIR) && zip -r ch33ter-vXXX.zip . -x "*.DS_Store"

run: all
	$(TARGET)

# Clean target
clean:
	rm -f $(TARGET) $(WIN_CROSS_TARGET) $(LIN_CROSS_TARGET)

# Phony targets
.PHONY: all clean run cross-win cross-lin