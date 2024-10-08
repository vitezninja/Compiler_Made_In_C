#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include "../utils/token.h"
#include "../utils/AST.h"
#include "../utils/error.h"

/**
 * Represents the state and context of the parser during the parsing process.
 * 
 * The `Parser` structure encapsulates the details necessary for converting a sequence 
 * of tokens into an abstract syntax tree (AST). It includes the following fields:
 * 
 * - `tokens`: A pointer to an array of `Token` pointers representing the sequence 
 *             of tokens to be parsed. The `Parser` holds a filtered copy of this 
 *             array but does not own the individual `Token` objects. The caller is 
 *             responsible for managing and freeing the individual `Token` objects 
 *             and the original token array.
 * 
 * - `tokenCount`: A `size_t` value indicating the total number of tokens in the 
 *                 `tokens` array. This value helps ensure the parser does not attempt 
 *                 to access tokens beyond the available range.
 * 
 * - `position`: A `size_t` value that serves as an index into the `tokens` array, 
 *               indicating the current token being processed by the parser. This 
 *               index is incremented as the parser progresses through the tokens.
 * 
 * - `ASTroot`: A pointer to the root `ASTNode` of the abstract syntax tree (AST) 
 *              generated by the parser. The AST represents the hierarchical structure 
 *              of the parsed source code.
 * 
 * - `errors`: A pointer to an array of `Error` pointers that capture any errors 
 *              encountered during parsing. The parser maintains and manages this array.
 * 
 * - `errorCount`: A `size_t` value indicating the number of errors recorded in the 
 *                  `errors` array.
 * 
 * - `errorsSize`: A `size_t` value indicating the allocated size of the `errors` array. 
 * 
 * The `Parser` struct is central to the parsing process, managing the context and state 
 * needed to navigate through the token stream and construct the corresponding AST.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Parser` object. 
 *       After use, the `Parser` should be properly freed using the `deleteParser` function 
 *       to avoid memory leaks. The caller is also responsible for managing and freeing 
 *       the individual `Token` objects and the original token array.
 */
typedef struct parser
{
    Token **tokens;         /** The array of token pointers owned by the parser. */
    size_t tokenCount;      /** The number of tokens in the array. */
    size_t position;        /** The current position in the token array. */
    ASTNode *ASTroot;       /** The root of the AST generated by the parser. */
    Error **errors;         /** An array of error pointers encountered during parsing. */
    size_t errorCount;      /** The number of errors recorded. */
    size_t errorsSize;      /** The allocated size of the errors array. */
} Parser;

/**
 * Creates a new `Parser` object and initializes it with a filtered list of tokens.
 * 
 * This function allocates memory for a `Parser` structure and initializes it with a copy of the provided tokens, 
 * filtering out any tokens that are whitespace or comments. The function reallocates the token array to fit 
 * only the relevant tokens.
 * 
 * @param tokens      A pointer to an array of `Token` pointers. The `Parser` will store a filtered version 
 *                    of this array, excluding whitespace and comments.
 * 
 * @param tokenCount  The total number of tokens in the `tokens` array.
 * 
 * @return A pointer to the newly created `Parser` object, or `NULL` if memory allocation fails or if the 
 *         `tokens` array is `NULL`.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Parser` object. This includes freeing 
 *       the `Parser` using `deleteParser` when it is no longer needed. The caller is also responsible for 
 *       managing the lifecycle of the individual `Token` objects provided in the `tokens` array, as the 
 *       `Parser` does not take ownership of these tokens or the original `tokens` array.
 * 
 * @note The `Parser` holds a filtered copy of the token array but does not own the individual `Token` objects 
 *       or the original `tokens` array. The caller should ensure to free the `Token` objects when they are 
 *       no longer needed. The `Parser` object itself should be freed using `deleteParser` when it is no 
 *       longer needed.
 */
Parser *createParser(Token **const tokens, const size_t count);

/**
 * Deletes a `Parser` object and frees its memory.
 * 
 * Frees the memory allocated for the `Parser` structure and its associated resources.
 * The function will free the memory for the filtered token array held by the `Parser`.
 * If an Abstract Syntax Tree (AST) root node exists, it will also be freed.
 * 
 * @param parser The `Parser` object to be deleted. If the parser is NULL, the function does nothing.
 * 
 * @note The `Parser` holds a copy of the filtered token array but does not own the individual 
 *       `Token` objects. It is the caller's responsibility to manage and free the memory 
 *       for the `Token` objects separately.
 * 
 * @note The `Parser` does not own the AST root node but it is the caller's responsibility 
 *       to manage and free the memory for the AST if needed. To avoid memory leaks, 
 *       it is advised that the caller obtains a copy of the AST using `getCopyAST` 
 *       before deleting the parser.
 */
void deleteParser(Parser *const parser);

/**
 * Retrieves a copy of the Abstract Syntax Tree (AST) from the `Parser`.
 * 
 * This function creates a duplicate of the AST root node held by the `Parser`.
 * It ensures that a new `ASTNode` structure is returned, which is a copy of the 
 * current AST root. If the `Parser` is not initialized or the AST root is NULL, 
 * the function will report an error and return NULL.
 * 
 * @param parser A pointer to the `Parser` object from which to copy the AST.
 *               The `Parser` must be initialized and must contain a valid AST root.
 * 
 * @return A pointer to a newly created `ASTNode` that is a copy of the parser's 
 *         AST root, or NULL if the `Parser` is not initialized, or if the AST root is NULL.
 * 
 * @note To avoid memory leaks, ensure that the returned `ASTNode` is properly managed
 *       and freed when no longer needed.
 */
ASTNode *getCopyAST(const Parser *const parser);

/**
 * Parses the input tokens and generates an Abstract Syntax Tree (AST) from them.
 * 
 * This function processes the tokens held by the `Parser` to construct an AST. It
 * initializes the parsing process, creating a structured representation of
 * the source code. The function should be called only once per `Parser` instance. 
 * If parsing has already been performed or if an error occurs during parsing,
 * the function will report the issue and return 0. If parsing is successful, it
 * will return 1.
 * 
 * @param parser A pointer to the `Parser` object containing the tokens to be parsed.
 *               The `Parser` must be initialized and should not have an existing
 *               AST root before parsing. The tokens in the `Parser` should be 
 *               appropriately filtered and prepared for parsing.
 * 
 * @return 1 if parsing is successful and the AST is created; 0 if there is an error
 *         (e.g., if the `Parser` is NULL, parsing has already been performed, or
 *         if parsing fails).
 * 
 * @note If parsing fails, the function will report an error to `stderr`. The caller
 *       should ensure that proper error handling and resource management are in place.
 *       To manage the resulting AST, the caller should check the return value and 
 *       handle the AST accordingly. If the `Parser` has a non-NULL `ASTroot` after
 *       parsing, it indicates that the parsing was successful.
 */
int parse(Parser *parser);

/**
 * Prints the Abstract Syntax Tree (AST) to the standard output.
 * 
 * This function outputs a visual representation of the AST generated by the parser.
 * It starts by checking the validity of the `Parser` object and whether the AST has
 * been generated. If the `Parser` is NULL or the AST root is not yet set, it reports
 * the issue to `stderr`. Otherwise, it proceeds to print the AST using the `printASTNode`
 * function.
 * 
 * @param parser A pointer to the `Parser` object containing the AST to be printed.
 *               The `Parser` must be initialized and have a valid AST root.
 * 
 * @return void
 * 
 * @note The function will report errors to `stderr` if:
 * 
 *       - The `Parser` is NULL.
 * 
 *       - The AST root has not been set (indicating that parsing has not yet occurred).
 * 
 * The function does not modify the `Parser` or its contents.
 */
void printParseTrees(const Parser *const parser);

#endif // PARSER_H