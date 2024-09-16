CC = gcc
CFLAGS = -g -Og -Wall -Wextra -std=gnu99

# Detect OS
ifeq ($(OS),Windows_NT)
	TARGET = cmc.exe
else 
	UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	TARGET = cmc.out
endif
endif

INCLUDES = -I./src -I./src/Lexer -I./src/Parser -I./src/VM -I./src/Validator -I./src/utils 
CFLAGS += $(INCLUDES)

SRCS = $(wildcard src/*.c src/Lexer/*.c src/Parser/*.c src/VM/*.c src/Validator/*.c src/utils/*.c)

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm

main.o: src/main.c src/VM/vm.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

# VM
vm.o: src/VM/vm.c src/VM/vm.h src/utils/token.h src/utils/error.h src/utils/AST.h src/utils/my_string.h src/Lexer/lexer.h src/Parser/parser.h src/Validator/validator.h
	$(CC) $(CFLAGS) -c src/VM/vm.c -o src/VM/vm.o

# Lexer
lexer.o: src/Lexer/lexer.c src/Lexer/lexer.h src/utils/token.h src/utils/my_string.h src/utils/error.h
	$(CC) $(CFLAGS) -c src/Lexer/lexer.c -o src/Lexer/lexer.o

# Parser
parser.o: src/Parser/parser.c src/Parser/parser.h src/utils/token.h src/utils/AST.h src/utils/error.h
	$(CC) $(CFLAGS) -c src/Parser/parser.c -o src/Parser/parser.o

# Validator
validator.o: src/Parser/validator.c src/Parser/validator.h src/utils/token.h src/utils/AST.h src/utils/hash_table.h src/utils/stack.h src/utils/error.h src/utils/my_string.h
	$(CC) $(CFLAGS) -c src/Parser/validator.c -o src/Parser/validator.o

# Utils
my_string.o: src/utils/my_string.c src/utils/my_string.h
	$(CC) $(CFLAGS) -c src/utils/my_string.c -o src/utils/my_string.o

token.o: src/utils/token.c src/utils/token.h
	$(CC) $(CFLAGS) -c src/utils/token.c -o src/utils/token.o

error.o: src/utils/error.c src/utils/error.h
	$(CC) $(CFLAGS) -c src/utils/error.c -o src/utils/error.o

AST.o: src/utils/AST.c src/utils/AST.h
	$(CC) $(CFLAGS) -c src/utils/AST.c -o src/utils/AST.o

stack.o: src/utils/stack.c src/utils/stack.h
	$(CC) $(CFLAGS) -c src/utils/stack.c -o src/utils/stack.o

linked_list.o: src/utils/linked_list.c src/utils/linked_list.h
	$(CC) $(CFLAGS) -c src/utils/linked_list.c -o src/utils/linked_list.o

hash_table.o: src/utils/hash_table.c src/utils/hash_table.h src/utils/linked_list.h
	$(CC) $(CFLAGS) -c src/utils/hash_table.c -o src/utils/hash_table.o

# Cleanup object files and executables
clean:
ifeq ($(OS),Windows_NT)
	-del $(subst /,\,$(OBJS)) $(TARGET)
else 
ifeq ($(UNAME_S),Linux)
	rm -f $(OBJS) $(TARGET)
endif
endif

# Valgrind check only on Linux
valgrind: $(TARGET)
ifneq ($(OS),Windows_NT)
ifeq ($(UNAME_S),Linux)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(TARGET) tests/parser_tests/test3.c
endif
endif

# Debug only on Linux
debug: $(TARGET)
ifneq ($(OS),Windows_NT)
ifeq ($(UNAME_S),Linux)
	gf2 ./$(TARGET) &
endif
endif

.PHONY: all clean valgrind debug
