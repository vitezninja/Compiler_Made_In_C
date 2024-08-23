CC = gcc
CFLAGS = -g -Og -Wall -Wextra -std=gnu99 -I./src -I./src/Lexer -I.src/utils -I.src/Parser

TARGET = main
TARGET_LIN = main.out

SRCS = $(wildcard src/*.c src/Lexer/*.c src/utils/*.c src/Parser/*.c)

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

lin: $(TARGET_LIN)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: src/main.c src/Lexer/lexer.h src/Parser/parser.h src/utils/file_reading.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

lexer.o: src/Lexer/lexer.c src/Lexer/lexer.h src/utils/token.h src/utils/my_string.h
	$(CC) $(CFLAGS) -c src/Lexer/lexer.c -o src/Lexer/lexer.o

parser.o: src/Parser/parser.c src/Parser/parser.h src/utils/token.h src/utils/AST.h
	$(CC) $(CFLAGS) -c src/Parser/parser.c -o src/Parser/parser.o

token.o: src/utils/token.c src/utils/token.h
	$(CC) $(CFLAGS) -c src/utils/token.c -o src/utils/token.o

AST.o: src/utils/AST.c src/utils/AST.h
	$(CC) $(CFLAGS) -c src/utils/AST.c -o src/utils/AST.o

my_string.o: src/utils/my_string.c src/utils/my_string.h
	$(CC) $(CFLAGS) -c src/utils/my_string.c -o src/utils/my_string.o

file_reading.o: src/utils/file_reading.c src/utils/file_reading.h
	$(CC) $(CFLAGS) -c src/utils/file_reading.c -o src/utils/file_reading.o

clean:
	-del $(subst /,\,$(OBJS)) $(TARGET).exe

clean_lin:
	rm -f $(OBJS) $(TARGET_LIN)

# Valgrind check
valgrind: $(TARGET_LIN)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(TARGET_LIN) tests/parser_tests/test3.c

.PHONY: all lin clean clean_lin valgrind
