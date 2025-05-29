#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <errno.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#include "utils/logger.h"
#include "utils/token.h"
#include "utils/arena.h"
#include "utils/linkedList.h"
#include "utils/error.h"

#define TEXT_BUFFER_SIZE 256

typedef struct Lexer
{
    Arena *utilsArena;
    Arena *tokenArena;
    LinkedList *error;
    LinkedList *tokens;
    HashTable *stringInterningTable;
    const char *sourceBuffer;
    size_t sourceBufferSize;
    size_t currentPosition;
    size_t line;
    size_t column;
} Lexer;

Lexer *lexer_create(Arena *utilsArena, Arena *tokenArena, HashTable *stringInterningTable, const char *sourceBuffer, size_t sourceBufferSize);

void lexer_lex(Lexer* lexer);

void lexer_print(const Lexer* lexer);

#endif // LEXER_H