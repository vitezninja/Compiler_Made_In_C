MAKEFLAGS += --no-print-directory
.DEFAULT_GOAL := all
.PHONY: all clean test valgrind release help

# === Configuration ===

CC := gcc
LD := gcc
STD := -std=gnu99

# Detect OS (Windows native CMD sets OS to Windows_NT)
UNAME_EXISTS := $(shell command -v uname 2> NUL)

ifeq ($(UNAME_EXISTS),)
	UNAME_S := Unknown
else
	UNAME_S := $(shell uname -s 2>/dev/null || echo Unknown)
endif

ifeq ($(OS),Windows_NT)
    HOST_OS := windows

	# Handle Git Bash / MSYS2 / MinGW
	ifneq (,$(findstring MINGW,$(UNAME_S)))
		HOST_OS := msys
	else ifneq (,$(findstring MSYS,$(UNAME_S)))
		HOST_OS := msys
	endif
else
    ifeq ($(UNAME_S),Linux)
        HOST_OS := linux
    else ifeq ($(UNAME_S),Darwin)
        HOST_OS := macos
    else ifeq ($(UNAME_S),FreeBSD)
        HOST_OS := freebsd
    else
        HOST_OS := unknown
    endif
endif

ifeq ($(HOST_OS),unknown)
    $(warning Unknown host OS: build might not work properly)
endif

$(info Detected OS: $(HOST_OS))
$(info Detected UNAME_S: $(UNAME_S))

# Set output file extension based on OS
ifeq ($(HOST_OS),windows)
	OUTPUT_EXTENSION ?= exe
else ifeq ($(HOST_OS),msys)
	OUTPUT_EXTENSION ?= exe
else
	OUTPUT_EXTENSION ?= out
endif

# Directories
SRC_DIR := src
BUILD_DIR := build
TEST_DIR := tests

DEFINES := -DDEBUG -DOVALIDATE
# -DOPARSE -DOLEX -DOVALIDATE -DPROFILE

# Flags
DISABLE_SANITIZERS ?= 0
DEV_FLAGS := $(STD) -Wall -Wextra -ggdb -Og -Wpedantic -Werror -Wshadow -Wstrict-prototypes -Wmissing-prototypes -Wno-unused-parameter -fstack-protector-strong -Iinclude $(DEFINES)
ifeq ($(HOST_OS),linux)
	ifneq ($(DISABLE_SANITIZERS),1)
		DEV_FLAGS += -fsanitize=address,undefined
	endif
endif
REL_FLAGS := $(STD) -Wall -Wextra -Wno-unused-parameter -O3 -Iinclude
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1

# Linker flags
LDFLAGS := -lm
ifeq ($(HOST_OS),linux)
	ifneq ($(DISABLE_SANITIZERS),1)
		LDFLAGS += -static-libasan
	endif
endif

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
VALGRIND_TEST_FILE := $(TEST_DIR)/test.cmc
LOG_FILE := compiler.log
TEST_LOG_FILE := $(TEST_DIR)/test.log

TARGET := cmc.$(OUTPUT_EXTENSION)

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
	@$(LD) $(CFLAGS) $(LDFLAGS) $^ -o "$@" && echo Target built successfully!
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
	@if exist $(TARGET) del $(TARGET)
	@if exist $(LOG_FILE) del $(LOG_FILE)
	@if exist $(TEST_LOG_FILE) del $(TEST_LOG_FILE)
else
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET)
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
valgrind:
ifeq ($(HOST_OS),linux)
	@$(MAKE) DISABLE_SANITIZERS=1
	valgrind $(VALGRIND_FLAGS) ./$(TARGET) $(VALGRIND_TEST_FILE)
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
