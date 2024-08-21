#include "AST.h"

/*****************************************************************************************************
                            PRIVATE AST FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/


/*****************************************************************************************************
                                PRIVATE AST FUNCTIONS START HERE
 *****************************************************************************************************/


/*****************************************************************************************************
                                PUBLIC AST FUNCTIONS START HERE                                
 *****************************************************************************************************/

ASTNode *createASTNode(const ASTType type, Token **const tokens, const size_t tokenCount, ASTNode **const children, const size_t childCount)
{
    ASTNode *astNode = (ASTNode *)malloc(sizeof(ASTNode)); 
    if (astNode == NULL)
    {
        fprintf(stderr, "Memory allocation for AST Node failed!\n");
        return NULL;
    }

    astNode->type = type;
    astNode->tokens = tokens;
    astNode->tokenCount = tokenCount;
    astNode->children = children;
    astNode->childCount = childCount;

    return astNode;
}

void deleteASTNode(ASTNode *const astNode)
{
    if (astNode == NULL)
    {
        fprintf(stderr, "ASTNode is NULL!\n");
        return;
    }

    for (size_t i = 0; i < astNode->childCount; ++i) 
    {
        deleteASTNode(astNode->children[i]);
    }
    free(astNode->children);
    free(astNode->tokens);
    free(astNode);
}

ASTNode *duplicateASTNode(ASTNode *const astNode)
{
    if (astNode == NULL)
    {
        fprintf(stderr, "ASTNode is NULL!\n");
        return NULL;
    }

    ASTNode *newNode = createASTNode(astNode->type, astNode->tokens, astNode->tokenCount, astNode->children, astNode->childCount);
    if (newNode == NULL)
    {
        fprintf(stderr, "Memory allocation for new AST Node failed!\n");
        return NULL;
    }
    
    return newNode;
}

//TODO:
void printASTNode(const ASTNode *const astNode)
{
    if (astNode == NULL)
    {
        return;
    }
}