#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#include "utils/linkedList.h"
#include "utils/arena.h"
#include "utils/token.h"
#include "utils/logger.h"
#include "utils/ast.h"

typedef struct Parser
{
    Arena *utilsArena;
    Arena *astArena;
    LinkedList *errors;
    LinkedList *tokens;
    AstNode *ast;
} Parser;

Parser *parser_create(Arena *utilsArena, Arena *astArena, LinkedList *tokens);

void parser_parse(Parser *parser);

void parser_print(const Parser *parser);

#endif // PARSER_H