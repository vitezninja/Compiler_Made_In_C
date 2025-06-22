/**
 * @file parser.h
 * @brief Header file for the parser module.
 * 
 * This file defines the Parser structure and functions for parsing tokens into an abstract syntax tree (AST).
 * It includes functions for creating a parser, parsing tokens, and printing the resulting AST.
 */

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

/**
 * @brief The parser structure.
 * 
 * This structure holds the state of the parser, including the arenas used for memory allocation,
 * linked lists for errors and tokens, and the abstract syntax tree (AST) being constructed.
 */
typedef struct Parser
{
    Arena *utilsArena;     /** Arena for utility allocations, such as errors and tokens */
    Arena *astArena;       /** Arena for AST allocations, used to store nodes created during parsing */
    LinkedList *errors;    /** Linked list of errors encountered during parsing */
    LinkedList *tokens;    /** Linked list of tokens to be parsed */
    AstNode *ast;          /** Pointer to the root of the abstract syntax tree (AST) being constructed */
    bool panic;            /** Flag indicating whether the parser is in a panic state due to an error */
} Parser;

/**
 * @brief Creates a new parser instance.
 * 
 * This function initializes a parser with the provided arenas and tokens.
 * It allocates memory for the parser structure and initializes its fields.
 * 
 * @param utilsArena Pointer to the arena used for utility allocations.
 * @param astArena Pointer to the arena used for AST allocations.
 * @param tokens Linked list of tokens to be parsed.
 * 
 * @return Pointer to the newly created Parser instance, or NULL if memory allocation fails.
 */
Parser *parser_create(Arena *utilsArena, Arena *astArena, LinkedList *tokens);

/**
 * @brief Parses the tokens into an abstract syntax tree (AST).
 * 
 * This function processes the linked list of tokens and constructs an abstract syntax tree (AST).
 * It handles syntax errors and populates the errors linked list if any issues are encountered during parsing
 * 
 * @param parser Pointer to the Parser instance to be used for parsing.
 */
void parser_parse(Parser *parser);

/**
 * @brief Parses global symbols in the tokens.
 * 
 * This function processes the tokens to identify and parse global symbols, such as variables and functions.
 * It constructs the necessary AST nodes for these symbols and adds them to the AST.
 * 
 * @param parser Pointer to the Parser instance to be used for parsing global symbols.
 * 
 * @note This function only handles global symbols and does not parse the entire AST.
 * @note Used in the validation phase to ensure that global symbols are correctly defined for importing.
 */
void parser_parseGlobalSymbols(Parser *parser);

/** 
 * @brief Prints the parser data structure.
 * 
 * This function prints the contents of the parser, including the errors and the abstract syntax tree (AST).
 * It is useful for debugging and understanding the state of the parser after parsing has been performed.
 * 
 * @param parser Pointer to the Parser instance to be printed.
*/
void parser_print(const Parser *parser);

#endif // PARSER_H