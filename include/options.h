/**
 * @file options.h
 * @brief Header file for command-line options parsing in the compiler.
 * 
 * This file defines the Options structure and functions for parsing command-line arguments
 * and managing compiler options. It includes flags for various compiler features,
 * such as debugging, optimization, and output file specification.
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

// Forward declaration of the Options structure
typedef struct Options Options;

#include "utils/logger.h"
#include "utils/bitset.h"

/**
 * @enum OptionFlags
 * @brief Bitfield flags representing supported command-line options.
 *
 * These flags indicate which compiler options have been enabled
 * through command-line arguments.
 */
typedef enum OptionFlags
{
    OPTION_FLAG_NONE,              /** No flags set. */
    OPTION_FLAG_HELP,              /** Print help message. */
    OPTION_FLAG_NO_LINK,           /** Compile source files without linking. */
    OPTION_FLAG_IS_OUTPUT_FILE,    /** Specify the output file. */
    OPTION_FLAG_WARN_ALL,          /** Enable all warnings. */
    OPTION_FLAG_WARN_ERRORS,       /** Treat warnings as errors. */
    OPTION_FLAG_DEBUG_INFO,        /** Include debugging information. */
    OPTION_FLAG_OPTIMIZATION,      /** Enable optimization. */
} OptionFlags;

/**
 * @struct Options
 * @brief Container for all parsed command-line arguments.
 */
struct Options
{
    Bitset64 flags;          /** BitSet to hold various flags. */
    char *outputFile;        /** Name or path of the output file, if specified. */
    char **files;            /** Array of strings representing source files to compile. */
    size_t fileCount;        /** Number of source files. */
    char **headerFiles;      /** Array of strings representing header file paths. */
    size_t headerCount;      /** Number of header files. */
};

/**
 * @brief Parses command-line arguments into an Options structure.
 *
 * Parses all supported flags and arguments.
 *
 * @param argc Number of arguments (from `main`).
 * @param argv Argument vector (from `main`).
 * @return A fully populated `Options` structure. Set `errno` to indicate the error.
 * 
 * @note The function allocates memory for the `Options` structure and its members.
 *       It is the caller's responsibility to free this memory using `options_free`.
 */
Options options_create(int argc, char** argv);

/**
 * @brief Frees dynamic memory allocated inside an Options structure.
 *
 * This function cleans up the memory allocated for source and header file arrays.
 * The `flags` bitset is assumed to be managed elsewhere or via a custom allocator.
 *
 * @param options Pointer to the Options struct to free.
 */
void options_free(Options *options);

/**
 * @brief Prints a human-readable summary of the parsed options.
 *
 * This is useful for debugging or displaying the compiler configuration state.
 *
 * @param options Pointer to the Options structure to print.
 */
void options_print(const Options *options);

/**
 * @brief Prints help information for command-line usage.
 *
 * Outputs a description of all supported flags and how to use the compiler.
 * Typically shown when `-h` is passed.
 * 
 * @param options Pointer to the Options structure.
 */
bool options_tryPrintHelp(const Options *options);

#endif // OPTIONS_H