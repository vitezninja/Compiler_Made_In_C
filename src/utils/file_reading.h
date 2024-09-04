#ifndef FILE_READING_H
#define FILE_READING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

/**
 * Represents a collection of flags and options for configuring the compiler.
 * 
 * The `Flags` structure holds various settings and options specified by the user
 * through command-line arguments. It includes the following fields:
 * 
 * - `onlyLex`: Indicates whether only lexical analysis should be performed.
 *              - 1 if only lexical analysis is requested (e.g., `-l` flag).
 *              - 0 otherwise.
 * 
 * - `help`: Indicates if help information should be displayed.
 *           - 1 if help is requested (e.g., `-h` flag).
 *           - 0 otherwise.
 * 
 * - `files`: An array of strings representing the source files to be compiled.
 * 
 * - `fileCount`: The number of source files specified in the `files` array.
 * 
 * - `isOutputFile`: Indicates whether an output file has been specified.
 *                   - 1 if an output file is specified (e.g., `-o` flag).
 *                   - 0 otherwise.
 * 
 * - `outputFile`: A string representing the name or path of the output file, if specified.
 * 
 * - `warnAll`: Indicates if all warnings should be enabled.
 *              - 1 if all warnings are enabled (e.g., `-Wall` flag).
 *              - 0 otherwise.
 * 
 * - `warnErrors`: Indicates if warnings should be treated as errors.
 *                 - 1 if warnings are treated as errors (e.g., `-Werror` flag).
 *                 - 0 otherwise.
 * 
 * - `debugInfo`: Indicates if debugging information should be included.
 *                - 1 if debugging information is included (e.g., `-g` flag).
 *                - 0 otherwise.
 * 
 * - `optimization`: Indicates if optimization should be enabled.
 *                   - 1 if optimization is enabled (e.g., `-O` flag).
 *                   - 0 otherwise.
 * 
 * - `headerFiles`: An array of strings representing header file paths specified by the user.
 * 
 * - `headerCount`: The number of header files specified in the `headerFiles` array.
 * 
 * - `libraryFiles`: An array of strings representing library file paths specified by the user.
 * 
 * - `libraryCount`: The number of library files specified in the `libraryFiles` array.
 * 
 * - `macros`: An array of strings representing macros defined by the user.
 * 
 * - `macroCount`: The number of macros specified in the `macros` array.
 * 
 * - `standard`: A string representing the specified C standard (e.g., `-std=` flag).
 * 
 * The `Flags` structure is used by various functions to manage the state and configuration of the compiler based on user input.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Flags` object. After use, the memory allocated for the
 *       `Flags` structure, including its dynamic arrays, should be released using the `freeFlags` function.
 */
typedef struct flags
{
    int onlyLex;             /** Flag to indicate lexical analysis only. */
    int help;                /** Flag to indicate if help is requested. */
    char **files;            /** Array of strings representing source files to compile. */
    size_t fileCount;        /** Number of source files. */
    int isOutputFile;        /** Flag to indicate if an output file is specified. */
    char *outputFile;        /** Name or path of the output file, if specified. */
    int warnAll;             /** Flag to enable all warnings. */
    int warnErrors;          /** Flag to treat warnings as errors. */
    int debugInfo;           /** Flag to include debugging information. */
    int optimization;        /** Flag to enable optimization. */
    char **headerFiles;      /** Array of strings representing header file paths. */
    size_t headerCount;      /** Number of header files. */
    char **libraryFiles;     /** Array of strings representing library file paths. */
    size_t libraryCount;     /** Number of library files. */
    char **macros;           /** Array of strings representing macros defined by the user. */
    size_t macroCount;       /** Number of macros. */
    char *standard;          /** String representing the specified C standard. */
} Flags;

/**
 * Parses and handles command-line arguments to initialize and configure the `Flags` structure.
 * 
 * This function processes the command-line arguments (`argc` and `argv`) to set various flags and
 * options within a newly allocated `Flags` structure. It dynamically allocates memory for the
 * `Flags` structure and its members, based on the provided arguments.
 * 
 * The function identifies different flags (e.g., `-l`, `-h`, `-o`, etc.) and options (e.g., file paths,
 * macros, library paths) and populates the corresponding fields in the `Flags` structure. It also
 * performs error handling for invalid or unsupported arguments, and if any memory allocation fails,
 * it cleans up and returns `NULL`.
 * 
 * @param argc The number of command-line arguments.
 * 
 * @param argv An array of pointers to the command-line argument strings.
 * 
 * @return A pointer to a dynamically allocated `Flags` structure containing the parsed command-line options,
 *         or `NULL` if an error occurs (such as invalid arguments or memory allocation failures).
 * 
 * @note The caller is responsible for freeing the returned `Flags` structure and its associated memory
 *       using `freeFlags` when it is no longer needed.
 */
Flags *parseArgs(int argc, char **argv);

/**
 * Frees memory associated with a `Flags` structure and its dynamically allocated members.
 * 
 * This function deallocates all memory allocated for the `Flags` structure, including any
 * dynamically allocated arrays and strings within the structure. If the `flags` pointer is `NULL`,
 * an error message is printed and the function returns immediately.
 * 
 * The function checks each dynamically allocated member of the `Flags` structure and frees it
 * appropriately. The `flags` structure itself is also freed at the end.
 * 
 * @param flags A pointer to the `Flags` structure to be freed. It is assumed to be dynamically allocated.
 * 
 * @note This function checks if the `flags` pointer is `NULL` before attempting to free its members.
 *       It also checks for each dynamically allocated member array to ensure it is not `NULL` before freeing.
 * 
 * @note After calling this function, the pointer to the `Flags` structure should not be used unless
 *       it is re-initialized, as the memory it points to will be deallocated.
 */
void freeFlags(Flags *flags);

/**
 * Reads the contents of multiple files into an array of strings.
 *
 * The `readFromFiles` function takes an array of file names, reads the contents of 
 * each file, and stores them in an array of strings. Each string in the returned array 
 * corresponds to the contents of one file.
 *
 * @param fileNames An array of `char*` representing the file names to read from. 
 *                  The array should contain `fileCount` elements.
 * @param fileCount The number of files to read, i.e., the size of the `fileNames` array.
 *
 * @return An array of `char*` where each element contains the contents of a corresponding file.
 *         Returns `NULL` if the `fileNames` array is `NULL` or if memory allocation fails.
 * 
 * @note The caller is responsible for freeing the memory allocated for the file contents 
 *       using `freeFileContent`. If a file cannot be read, the corresponding 
 *       entry in the returned array may be `NULL`.
 */
char **readFromFiles(char **fileNames, const size_t fileCount);

/**
 * Frees the memory allocated for the contents of multiple files.
 *
 * The `freeFileContent` function deallocates the memory used to store the contents 
 * of multiple files, as well as the memory used for the array holding those contents.
 *
 * @param FileContents An array of `char*` where each element points to the contents 
 *                     of a file. The array should contain `fileCount` elements.
 * @param fileCount The number of files, i.e., the number of elements in the 
 *                  `FileContents` array.
 *
 * @note If `FileContents` is `NULL`, the function does nothing and logs an error 
 *       message to `stderr`. The caller should ensure `FileContents` is properly 
 *       allocated before passing it to this function.
 */
void freeFileContent(char **FileContents, const size_t fileCount);

#endif // FILE_READING_H