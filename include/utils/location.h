/**
 * @file location.h
 * @brief Header file for source location representation.
 * 
 * This file defines the SourceLocation structure and functions for printing
 * the location of tokens in the source code. It is used to track where tokens
 * appear in the source code.
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "utils/logger.h"

/**
 * @struct SourceLocation
 * @brief Represents the location of a token in the source code.
 *
 * Includes the file name, line number, and column number.
 */
typedef struct SourceLocation
{
    const char *fileName;     /** Name of the source file */
    uint32_t line;            /** Line number in the source file */
    uint32_t column;          /** Column number in the source file */
    uint32_t lineStart;       /** Start line number in the source file */
    size_t length;            /** Length of characters in the source file */
} SourceLocation;

/**
 * @brief Prints the SourceLocation to stdout.
 *
 * This function outputs the file name, line, and column information of a SourceLocation
 * in a human-readable format. It is typically used for debugging purposes.
 *
 * @param location  Pointer to the SourceLocation to print.
 */
void sourceLocation_print(const SourceLocation *location);

#endif // LOCATION_H