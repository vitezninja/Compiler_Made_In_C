#include "AST.h"

/*****************************************************************************************************
                            PRIVATE AST FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/*****************************************************************************************************
                                PRIVATE AST FUNCTIONS START HERE
 *****************************************************************************************************/

/**
 * Lookup table for ASTType
 */
static const char *const ASTTypes[] = {
    "PROGRAM",
    "GLOBAL_VARIABLE_DECLARATION",
    "FUNCTION_DECLARATION",
    "FUNCTION_DEFINITION",
    "ENUM",
    "STRUCT",
    "UNION",
    "PARAMETER_LIST",
    "ENUM_LIST",
    "MEMBER_LIST",
    "LABELED_STATEMENT",
    "EXPRESSION_STATEMENT",
    "RETURN_STATEMENT",
    "BREAK_STATEMENT",
    "CONTINUE_STATEMENT",
    "GOTO_STATEMENT",
    "COMPOUND_STATEMENT",
    "LOCAL_VARIABLE_DECLARATION",
    "FOR_ITERATION_STATEMENT",
    "WHILE_ITERATION_STATEMENT",
    "DO_ITERATION_STATEMENT",
    "IF_STATEMENT",
    "SWITCH_STATEMENT",
    "SWITCH_BODY",
    "LITERAL",
    "BINARY_EXPRESSION",
    "UNARY_EXPRESSION",
    "IDENTIFIER_EXPRESSION",
    "PARENTHESES_EXPRESION",
    "TYPE_CAST_EXPRESION",
    "ASSIGNEMENT_EXPRESION",
    "FUNCTION_CALL",
    "FUNCTION_CALL_PARAMETER_LIST",
};


/*****************************************************************************************************
                                PUBLIC AST FUNCTIONS START HERE                                
 *****************************************************************************************************/

/**
 * Creates a new `ASTNode` with the specified type, tokens, and children.
 * 
 * Allocates memory for a new `ASTNode` and initializes its fields with the provided
 * type, tokens, and child nodes. The function does not take ownership of the tokens
 * arrays; it merely copies the pointers. But take ownership of the children array.
 * 
 * @param type The type of the AST node.
 * 
 * @param tokens An array of tokens associated with the node (must be dynamically allocated).
 * 
 * @param tokenCount The number of tokens in the `tokens` array.
 * 
 * @param children An array of child nodes (must be dynamically allocated).
 * 
 * @param childCount The number of child nodes in the `children` array.
 * 
 * @return A pointer to the newly created `ASTNode`, or NULL if memory allocation fails.
 * 
 * @note The caller is responsible for managing the memory of the `tokens` array. The
 *       `ASTNode` takes ownership of the `children` array and will free it when the
 *       `ASTNode` is deleted. To avoid memory leaks, it is advised to use the
 *       `deleteASTNode` function to clean up the `ASTNode` and its resources.
 */
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

/**
 * Deletes an `ASTNode` and frees its memory.
 * 
 * Recursively deletes all child nodes, the array of child nodes, and the array of tokens
 * associated with the node. It also frees the memory allocated for the `ASTNode` itself.
 * 
 * @param astNode The `ASTNode` to be deleted.
 * 
 * @note The function assumes that the `tokens` array and `children` array are dynamically allocated.
 *       It is the caller's responsibility to manage the memory of individual tokens.
 */
void deleteASTNode(ASTNode *const astNode)
{
    if (astNode == NULL)
    {
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

/**
 * Creates a duplicate of an `ASTNode`.
 * 
 * Allocates memory for a new `ASTNode` and copies the type, tokens, and child nodes
 * from the original node. It does not create deep copies of the tokens and children;
 * they are shared with the original node.
 * 
 * @param astNode The `ASTNode` to be duplicated.
 * 
 * @return A pointer to the duplicated `ASTNode`, or NULL if memory allocation fails.
 * 
 * @note The caller is responsible for managing the memory of the `tokens` array. The
 *       `ASTNode` takes ownership of the `children` array and will free it when the
 *       `ASTNode` is deleted. To avoid memory leaks, it is advised to use the
 *       `deleteASTNode` function to clean up the `ASTNode` and its resources.
 */
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

/**
 * Recursively prints an Abstract Syntax Tree (AST) node with indentation.
 * 
 * This function prints the details of the AST node, including its type, tokens, and children.
 * It formats the output to visually represent the tree structure using ASCII characters for tree nodes.
 * 
 * @param astNode Pointer to the `ASTNode` to be printed. If NULL, the function returns immediately.
 * 
 * @param indent The current indentation string. This is used to format the tree structure.
 * 
 * @param isLast Indicates whether the current node is the last child of its parent. This affects the tree formatting.
 */
void printASTNode(const ASTNode *const astNode, char *indent, int isLast)
{
    if (astNode == NULL)
    {
        return;
    }

    char *marker = isLast ? "└── " : "├── ";
    printf("%s%s%s\n", indent, marker, ASTTypes[astNode->type]);

    char newIndent[256];
    snprintf(newIndent, sizeof(newIndent), "%s%s", indent, isLast ? "    " : "│   ");

    //Print tokens
    
    for (size_t i = 0; i < astNode->tokenCount; i++)
    {
        if (i + 1 >= astNode->tokenCount && astNode->childCount == 0)
        {
            printf("%s└── ", newIndent);
        }
        else
        {
            printf("%s├── ", newIndent);
        }
        
        printToken(astNode->tokens[i]);
    }

    //Print children
    for (size_t i = 0; i < astNode->childCount; i++)
    {
        printASTNode(astNode->children[i], newIndent, i == astNode->childCount - 1);
    }
}