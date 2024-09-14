#ifndef VALIDATOR_H
#define VALIDATOR_H

#include "../src/utils/stack.h"
#include "../src/utils/hashTable.h"
#include "../src/utils/AST.h"
#include "../src/utils/token.h"
#include "../src/utils/error.h"
#include "../src/utils/my_string.h"

/**
 * Represents the state of the validator used for semantic analysis.
 *
 * The `Validator` struct stores the necessary information to perform semantic
 * validation of an Abstract Syntax Tree (AST). It tracks variable scopes, 
 * the root of the AST, and any errors encountered during the validation process.
 *
 * This structure contains information about the global scope, all nested scopes,
 * and any errors that occur during validation, allowing for proper semantic analysis
 * of the parsed code.
 *
 * Members:
 * - `globalScope`: A pointer to a `HashTable` representing the global scope, used to store
 *                  globally declared variables, functions, and other identifiers.
 * 
 * - `scopes`: A pointer to a `Stack` of scopes, where each scope contains local variables and 
 *             symbols specific to the current block or function being validated.
 * 
 * - `ASTroot`: A pointer to the root of the Abstract Syntax Tree (AST) representing the parsed
 *              source code. This is the tree that will be validated for semantic correctness.
 * 
 * - `errors`: An array of pointers to `Error` structures representing any semantic errors
 *             encountered during validation.
 * 
 * - `errorCount`: The number of semantic errors recorded in the `errors` array.
 * 
 * - `errorsSize`: The total size of the allocated `errors` array. This is used to manage
 *                 dynamic resizing of the array when new errors are encountered.
 */
typedef struct validator
{
    HashTable *globalScope;     /** Global scope for declared symbols (variables, functions). */
    Stack *scopes;              /** Stack to track scopes (local variables and block scopes). */
    ASTNode *ASTroot;           /** Root node of the Abstract Syntax Tree (AST). */
    Error **errors;             /** An array of error pointers encountered during validation. */
    size_t errorCount;          /** The number of errors recorded. */
    size_t errorsSize;          /** The allocated size of the errors array. */
} Validator;

Validator *createValidator(ASTNode *ASTroot);

void deleteValidator(Validator *validator);

int validate(Validator *validator);

ASTNode *copyASTNode(const Validator *const validator);

#endif