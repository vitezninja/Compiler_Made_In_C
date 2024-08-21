#ifndef AST_H
#define AST_H

#include "../utils/token.h"

//TODO:
//Add AST types
typedef enum astType
{
    AST_PROGRAM,
    AST_GLOBAL_VARIABLE_DECLARATION,
    AST_FUNCTION_DECLARATION,
    AST_FUNCTION_DEFINITION,
    AST_ENUM,
    AST_STRUCT,
    AST_UNION,
    AST_PARAMETER_LIST,
    AST_ENUM_LIST,
    AST_MEMBER_LIST,
    AST_LABELED_STATEMENT,
    AST_EXPRESSION_STATEMENT,
    AST_RETURN_STATEMENT,
    AST_BREAK_STATEMENT,
    AST_CONTINUE_STATEMENT,
    AST_GOTO_STATEMENT,
    AST_COMPOUND_STATEMENT,
    AST_LOCAL_VARIABLE_DECLARATION,
    AST_FOR_ITERATION_STATEMENT,
    AST_WHILE_ITERATION_STATEMENT,
    AST_DO_ITERATION_STATEMENT,
    AST_IF_STATEMENT,
    AST_SWITCH_STATEMENT,
    AST_SWITCH_BODY,
    AST_LITERAL,
    AST_BINARY_EXPRESSION,
    AST_UNARY_EXPRESSION,
    AST_IDENTIFIER_EXPRESSION,
    AST_PARENTHESES_EXPRESION,
} ASTType;

typedef struct astNode
{
    ASTType type;
    Token **tokens;
    size_t tokenCount;
    struct astNode **children;
    size_t childCount;
} ASTNode;

ASTNode *createASTNode(const ASTType type, Token **const tokens, const size_t tokenCount, ASTNode **const children, const size_t childCount);

void deleteASTNode(ASTNode *const astNode);

ASTNode *duplicateASTNode(ASTNode *const astNode);

//TODO:
void printASTNode(const ASTNode *const astNode);

#endif