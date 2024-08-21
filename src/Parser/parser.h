#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include "../utils/token.h"
#include "../utils/AST.h"

typedef struct parser
{
    Token **tokens;
    size_t tokenCount;
    size_t position;
    ASTNode *ASTroot;
    size_t astCount;
} Parser;

Parser *createParser(Token **const tokens, const size_t count);

void deleteParser(Parser *const parser);

void parse(Parser *parser);

ASTNode *getCopyAST(Parser *parser);

void printParseTrees(const Parser *const parser);

#endif