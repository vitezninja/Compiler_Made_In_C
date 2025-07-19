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

struct Validator 
{
    Arena *utilsArena;       /** Arena for utility allocations, such as errors */
    AstNode *ast;            /** Pointer to the root of the abstract syntax tree (AST) to be validated */
    LinkedList *symbolStack; /** Linked list of symbols currently in scope */
    HashTable *typeTable;    /** Hash table for storing types */
    LinkedList *errors;      /** Linked list of errors encountered during validation */
};

Validator* validator_create(Arena *utilsArena, AstNode *ast);

void validator_validate(Validator *validator);

void validator_print(const Validator *validator);

#endif // VALIDATOR_H