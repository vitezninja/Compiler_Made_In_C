#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include "../utils/token.h"
#include "../utils/AST.h"

/**
 * Represents the state and context of the parser during the parsing process.
 * 
 * The `Parser` structure encapsulates the details necessary for converting a sequence 
 * of tokens into an abstract syntax tree (AST). It includes the following fields:
 * 
 * - `tokens`: A pointer to an array of `Token` pointers that represent the sequence 
 *             of tokens to be parsed. The `Parser` owns this array, meaning it is 
 *             responsible for freeing the array itself, but it does not own the 
 *             individual `Token` objects pointed to by the array elements.
 * 
 * - `tokenCount`: A `size_t` value indicating the total number of tokens in the `tokens` array.
 *                 This value helps in ensuring that the parser does not attempt to access 
 *                 tokens beyond the available range.
 * 
 * - `position`: A `size_t` value that serves as an index into the `tokens` array, indicating 
 *               the current token being processed by the parser. As the parser progresses 
 *               through the tokens, this index is incremented.
 * 
 * - `ASTroot`: A pointer to the root `ASTNode` of the abstract syntax tree (AST) generated 
 *              by the parser. The AST represents the hierarchical structure of the parsed 
 *              source code.
 * 
 * The `Parser` struct is central to the parsing process, managing the context and state 
 * needed to navigate through the token stream and construct the corresponding AST.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Parser` object. 
 *       After use, the `Parser` should be properly freed using the `deleteParser` function 
 *       to avoid memory leaks.
 */
typedef struct parser
{
    Token **tokens;    /** The array of token pointers owned by the parser. */
    size_t tokenCount; /** The number of tokens in the array. */
    size_t position;   /** The current position in the token array. */
    ASTNode *ASTroot;  /** The root of the AST generated by the parser. */
} Parser;

Parser *createParser(Token **const tokens, const size_t count);

void deleteParser(Parser *const parser);

int parse(Parser *parser);

ASTNode *getCopyAST(const Parser *const parser);

void printParseTrees(const Parser *const parser);

#endif