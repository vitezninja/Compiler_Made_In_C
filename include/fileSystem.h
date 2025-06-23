/**
 * @file fileSystem.h
 * @brief Header file for file system operations.
 * 
 * This file defines the File structure and functions for reading files from the file system.
 * It includes functions for reading a file into memory, freeing the file resources,
 */

#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Forward declaration of the File structure
typedef struct File File;

#include "utils/logger.h"

/**
 * @struct File
 * 
 * @brief Represents a file in the file system.
 * 
 * This structure holds the name of the file, a pointer to the source buffer containing the file's contents,
 * and the size of the source buffer.
 */
struct File 
{
    const char* name;           /** Name of the file */
    const char *sourceBuffer;   /** Pointer to the source buffer */
    size_t sourceBufferSize;    /** Size of the source buffer */
};

/**
 * @brief Reads a file from the file system into memory.
 * 
 * This function attempts to open a file with the given name, reads its contents into a dynamically allocated buffer,
 * and returns a File structure containing the file name, the buffer, and its size.
 * If the file cannot be opened, is empty, or if any error occurs during reading, it returns an empty File structure.
 * 
 * @param fileName The name of the file to read.
 * 
 * @return A File structure containing the file name, source buffer, and size.
 * 
 * @note Sets `errno` to indicate the error if the file cannot be opened or read.
 */
File fileSystem_readFile(const char* fileName);

/**
 * @brief Frees the resources allocated for a File.
 * 
 * This function deallocates the memory used by the file's source buffer and resets the file structure.
 * 
 * @param file Pointer to the File structure to be freed.
 */
void fileSystem_free(File* file);

/**
 * @brief Prints the contents of the file to the standard output.
 * 
 * This function prints the name of the file and its contents to the standard output.
 * It is useful for debugging purposes to verify the contents of the file.
 * 
 * @param file Pointer to the File structure containing the file information.
 */
void fileSystem_print(const File* file);

#endif // FILE_SYSTEM_H