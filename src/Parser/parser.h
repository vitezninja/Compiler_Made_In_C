#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "../utils/token.h"

typedef struct parser
{
    Token **tokens;
    size_t tokenCount;
    size_t position;
    int *ASTRoot;
} Parser;

Parser *createParser(Token **tokens, const size_t count);

void deleteParser(Parser *parser);

void parse(Parser *parser);

void printParseTree(Parser *parser);

#endif