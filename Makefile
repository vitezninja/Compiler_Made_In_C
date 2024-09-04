CC = gcc
CFLAGS = -g -Og -Wall -Wextra -std=gnu99

TARGET = main
TARGET_LIN = main.out

INCLUDES = -I./src -I./src/Lexer -I./src/Parser -I./src/VM -I./src/utils
CFLAGS += $(INCLUDES)

SRCS = $(wildcard src/*.c src/Lexer/*.c src/Parser/*.c src/VM/*.c src/utils/*.c)

OBJS = $(SRCS:.c=.o)

# Windows
all: $(TARGET)

# Linux
lin: $(TARGET_LIN)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: src/main.c src/VM/vm.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

vm.o: src/VM/vm.c src/VM/vm.h src/utils/file_reading.h src/utils/token.h src/Lexer/lexer.h src/Parser/parser.h src/utils/AST.h
	$(CC) $(CFLAGS) -c src/VM/vm.c -o src/VM/vm.o

file_reading.o: src/utils/file_reading.c src/utils/file_reading.h src/utils/my_string.h
	$(CC) $(CFLAGS) -c src/utils/file_reading.c -o src/utils/file_reading.o

my_string.o: src/utils/my_string.c src/utils/my_string.h
	$(CC) $(CFLAGS) -c src/utils/my_string.c -o src/utils/my_string.o

token.o: src/utils/token.c src/utils/token.h
	$(CC) $(CFLAGS) -c src/utils/token.c -o src/utils/token.o

lexer.o: src/Lexer/lexer.c src/Lexer/lexer.h src/utils/token.h src/utils/my_string.h src/utils/error.h
	$(CC) $(CFLAGS) -c src/Lexer/lexer.c -o src/Lexer/lexer.o

error.o: src/utils/error.c src/utils/error.h
	$(CC) $(CFLAGS) -c src/utils/error.c -o src/utils/error.o

parser.o: src/Parser/parser.c src/Parser/parser.h src/utils/token.h src/utils/AST.h
	$(CC) $(CFLAGS) -c src/Parser/parser.c -o src/Parser/parser.o

AST.o: src/utils/AST.c src/utils/AST.h
	$(CC) $(CFLAGS) -c src/utils/AST.c -o src/utils/AST.o

# Clean on windows
clean:
	-del $(subst /,\,$(OBJS)) $(TARGET).exe

# Clean on linux
clean_lin:
	rm -f $(OBJS) $(TARGET_LIN)

# Valgrind check
valgrind: $(TARGET_LIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(TARGET_LIN) tests/parser_tests/test3.c

# Debug on Linux with gdb with gf2 frontend
debug: $(TARGET_LIN)
	gf2 ./$(TARGET_LIN) &

.PHONY: all lin clean clean_lin valgrind debug
