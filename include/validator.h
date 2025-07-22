/**
 * @file validator.h
 * @brief Header file for the Validator module.
 * 
 * This module provides functionality for validating an abstract syntax tree (AST)
 * and managing types and symbols within a compiler.
 */
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

typedef struct Validator Validator;

#include "utils/arena.h"
#include "utils/ast.h"
#include "utils/linkedList.h"
#include "utils/hashTable.h"
#include "utils/logger.h"

/**
 * @brief Structure representing a Validator.
 * 
 * This structure holds the necessary components for validating an AST,
 * including the utility arena for memory management, the AST itself, a symbol stack,
 * a type table, and a list of errors encountered during validation.
 */
struct Validator 
{
    Arena *utilsArena;       /** Arena for utility allocations, such as errors */
    AstNode *ast;            /** Pointer to the root of the abstract syntax tree (AST) to be validated */
    LinkedList *symbolStack; /** Linked list of symbols currently in scope */
    HashTable *typeTable;    /** Hash table for storing types */
    LinkedList *errors;      /** Linked list of errors encountered during validation */
};

/**
 * @brief Creates a Validator instance.
 * 
 * This function initializes a Validator with the provided utility arena and AST.
 * It allocates memory for the Validator structure and sets its initial state.
 * 
 * @param utilsArena Pointer to the utility arena for memory management.
 * @param ast Pointer to the root of the AST to be validated.
 * @return Pointer to the created Validator instance, or NULL if allocation fails.
 */
Validator* validator_create(Arena *utilsArena, AstNode *ast);

/**
 * @brief Validates the AST using the Validator.
 * 
 * This function performs a series of validation passes on the AST,
 * initializing the symbol stack and type table, and checking for errors.
 * It ensures that the AST is well-formed and adheres to the language's rules.
 * 
 * @param validator Pointer to the Validator instance to use for validation.
 */
void validator_validate(Validator *validator);

/**
 * @brief Prints the Validator's state.
 * 
 * This function outputs the current state of the Validator, including
 * the utility arena and the AST structure. It is useful for debugging purposes.
 * 
 * @param validator Pointer to the Validator instance to print.
 */
void validator_print(const Validator *validator);

#endif // VALIDATOR_H