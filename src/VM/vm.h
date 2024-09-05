#ifndef VM_H
#define VM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/my_string.h"
#include "../utils/token.h"
#include "../Lexer/lexer.h"
#include "../Parser/parser.h"
#include "../utils/AST.h"

/**
 * Executes the virtual machine (VM) process for compiling a source file.
 * 
 * This function handles the entire process of reading the input files, lexing the content into tokens,
 * parsing the tokens into an abstract syntax tree (AST), and handling errors or specific user requests 
 * such as lexing-only mode.
 * 
 * The function follows these steps:
 * 1. Parses the command-line arguments to set the compilation flags.
 * 2. Reads the content of the specified source files.
 * 3. Creates a lexer to analyze the input content and generate tokens.
 * 4. If requested, only lexes the input and prints the tokens.
 * 5. If further processing is required, creates a parser, parses the tokens, and generates the AST.
 * 6. Prints errors if any are encountered during lexing or parsing.
 * 7. Manages memory cleanup for all dynamically allocated resources.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * 
 * @return Returns `0` on success, or `-1` on failure.
 * 
 * @note The function handles multiple steps and has multiple exit points to manage errors appropriately.
 *       All dynamically allocated memory is freed before returning from any point in the function to prevent memory leaks.
 * 
 * @note The function currently supports handling only a single input file and does not process multiple files concurrently.
 * 
 * @note The caller is responsible for providing valid command-line arguments and input files to ensure proper execution.
 */
int runVM(int argc, char **argv);

#endif // VM_H