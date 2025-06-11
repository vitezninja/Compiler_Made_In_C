MAKEFLAGS += --no-print-directory
.DEFAULT_GOAL := all
.PHONY: all clean test valgrind release help

# === Configuration ===

CC := gcc
LD := gcc
STD := -std=gnu99

# Detect OS (Windows native CMD sets OS to Windows_NT)
ifeq ($(OS),Windows_NT)
    HOST_OS := windows
else
    UNAME_S := $(shell uname -s 2>/dev/null || echo Unknown)

    ifeq ($(UNAME_S),Linux)
        HOST_OS := linux
    else ifeq ($(UNAME_S),Darwin)
        HOST_OS := macos
    else ifeq ($(UNAME_S),FreeBSD)
        HOST_OS := freebsd
    else
        HOST_OS := unknown
    endif

    # Handle Git Bash / MSYS2 / MinGW
    ifneq (,$(findstring MINGW,$(UNAME_S)))
        HOST_OS := windows
    endif

    ifneq (,$(findstring MSYS,$(UNAME_S)))
        HOST_OS := windows
    endif
endif

ifeq ($(HOST_OS),unknown)
    $(warning Unknown host OS: build might not work properly)
endif

$(info Detected OS: $(HOST_OS))

# Set output file extension based on OS
ifeq ($(HOST_OS),windows)
	OUTPUT_EXTENSION ?= exe
else
	OUTPUT_EXTENSION ?= out
endif

# Directories
SRC_DIR := src
BUILD_DIR := build
TEST_DIR := tests

# Flags
DEV_FLAGS := $(STD) -Wall -Wextra -ggdb -Og -lm -Wpedantic -Werror -Wshadow -Wstrict-prototypes -Wmissing-prototypes -Wno-unused-parameter -fstack-protector-strong -Iinclude -DDEBUG
ifneq ($(HOST_OS),windows)
	DEV_FLAGS += -fsanitize=address,undefined
endif
REL_FLAGS := $(STD) -Wall -Wextra -Wno-unused-parameter -O3 -Iinclude
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1

# Default
BUILD_TYPE ?= dev
ifeq ($(BUILD_TYPE),dev)
    CFLAGS := $(DEV_FLAGS)
else
    CFLAGS := $(REL_FLAGS)
endif

# Source Files
SRC := $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(SRC_DIR)/*/*.c)
SRC += $(wildcard $(SRC_DIR)/*/*/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))
DEPS := $(OBJ:.o=.d)
VALGRIND_TEST_FILE := $(TEST_DIR)/valgrind_test.cmc
LOG_FILE := compiler.log
TEST_LOG_FILE := $(TEST_DIR)/test.log

TARGET := $(BUILD_DIR)/cmc.$(OUTPUT_EXTENSION)

# === Rules ===

all: $(TARGET)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
ifeq ($(HOST_OS),windows)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
else
	@mkdir -p "$(dir $@)"
endif
	@$(CC) $(CFLAGS) -MMD -c "$<" -o "$@" && echo $< compiled successfully!

# Link target
$(TARGET): $(OBJ) | $(BUILD_DIR)
	@$(LD) $(CFLAGS) $^ -o "$@" && echo Target built successfully!
	@echo Output file: $(TARGET)

$(BUILD_DIR):
ifeq ($(HOST_OS),windows)
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
else
	@mkdir -p "$(BUILD_DIR)"
endif

# Clean build
clean:
ifeq ($(HOST_OS),windows)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@if exist $(LOG_FILE) del $(LOG_FILE)
	@if exist $(TEST_LOG_FILE) del $(TEST_LOG_FILE)
else
	@rm -rf $(BUILD_DIR)
	@rm -f $(LOG_FILE)
	@rm -f $(TEST_LOG_FILE)
endif
	@echo Build directory removed.

# Run tests
test: $(TARGET)
ifeq ($(HOST_OS),windows)
	@$(TEST_DIR)/test_script.bat
else ifeq ($(HOST_OS),linux)
	@$(TEST_DIR)/test_sript.sh
else ifeq ($(HOST_OS),macos)
	@$(TEST_DIR)/test_script.sh
else
	@echo "Test script is not supported on $(HOST_OS)"
endif

# Run with valgrind
valgrind: $(TARGET)
ifeq ($(HOST_OS),linux)
	valgrind $(VALGRIND_FLAGS) $(TARGET) $(VALGRIND_TEST_FILE)
else ifeq ($(HOST_OS),macos)
	valgrind $(VALGRIND_FLAGS) $(TARGET) ${VALGRIND_TEST_FILE}
else
	@echo "Valgrind is not supported on $(HOST_OS)"
endif

# Release build
release:
	@$(MAKE) BUILD_TYPE=release

# Help message
help:
	@echo "Available targets:"
	@echo "  all       - Build the project (default)"
	@echo "  clean     - Remove build directory"
	@echo "  test      - Run tests"
	@echo "  valgrind  - Run target with Valgrind (Linux/macOS only)"
	@echo "  release   - Build with release flags"
	@echo "  help      - Show this help message"

-include $(DEPS)
