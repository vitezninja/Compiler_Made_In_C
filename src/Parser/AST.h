#ifndef AST_H
#define AST_H

#include "../utils/token.h"

//TODO:
//Add AST types
typedef enum astType
{
    AST_Expression,
    Statement,
} ASTType;

typedef struct astNode ASTNode;

typedef enum astDataType
{
    AST_DATA_FIXED,
    AST_DATA_MULTIPLE,
} ASTDataType;

typedef struct astNodeFixed {
    ASTNode *left;
    ASTNode *right;
    ASTNode *next;
} ASTNodeFixed;

typedef struct astNodeMultipleChildren {
    ASTNode **children;
    size_t childCount;
} ASTNodeMultipleChildren;

typedef union ASTNodeData {
    ASTNodeFixed fixed;
    ASTNodeMultipleChildren multi;
} ASTNodeData;

struct astNode
{
    ASTType type;
    Token *token;
    ASTDataType dataType;
    ASTNodeData data;
};

ASTNodeData createASTNodeData(const ASTDataType type, ASTNode **const children, const size_t childCount);

ASTNode *createASTNode(const ASTType type, Token *const token, const ASTDataType dataType, const ASTNodeData data);

void deleteASTNode(ASTNode *const astNode);

void printASTNode(const ASTNode *const astNode);

#endif