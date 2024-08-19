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

ASTNodeData createASTNodeData(const ASTDataType type, ASTNode **const children, const size_t childCount)
{
    ASTNodeData data;
    if (type == AST_DATA_FIXED)
    {
        if (childCount > 3)
        {
            //TODO:
            return;
        }
        ASTNodeFixed fixed;
        if (childCount >= 1)
        {
            fixed.left = children[0];
        }
        if (childCount >= 2)
        {
            fixed.right = children[1];
        }
        if (childCount == 3)
        {
            fixed.next = children[2];
        }

        data.fixed = fixed;
    }
    else
    {
        ASTNodeMultipleChildren multi;
        multi.children = children;
        multi.childCount = childCount;
        data.multi = multi;
    }

    return data;
}

ASTNode *createASTNode(const ASTType type, Token *const token, const ASTDataType dataType, const ASTNodeData data)
{
    ASTNode *astNode = (ASTNode *)malloc(sizeof(ASTNode)); 
    if (astNode == NULL)
    {
        fprintf(stderr, "Memory allocation for AST Node failed!\n");
        return NULL;
    }

    astNode->type = type;
    astNode->token = token;
    astNode->dataType = dataType;
    astNode->data = data;

    return astNode;
}

void deleteASTNode(ASTNode *const astNode)
{
    if (astNode == NULL)
    {
        return;
    }

    if (astNode->dataType == AST_DATA_FIXED)
    {
        if (astNode->data.fixed.left != NULL)
        {
            deleteASTNode(astNode->data.fixed.left);
        }
        if (astNode->data.fixed.right != NULL)
        {
            deleteASTNode(astNode->data.fixed.right);
        }
        if (astNode->data.fixed.next != NULL)
        {
            deleteASTNode(astNode->data.fixed.next);
        }
    }
    else
    {
        for (size_t i = 0; i < astNode->data.multi.childCount; ++i) 
        {
            deleteASTNode(astNode->data.multi.children[i]);
        }
        free(astNode->data.multi.children);
    }

    free(astNode);
}

//TODO:
void printASTNode(const ASTNode *const astNode)
{
    if (astNode == NULL)
    {
        return;
    }
}