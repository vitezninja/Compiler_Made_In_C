#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// Forward declaration of the File structure
struct File;

#include "utils/logger.h"

typedef struct File 
{
    const char* name;
    const char *sourceBuffer;
    size_t sourceBufferSize;
} File;

// Set `errno` to indicate the error.
File fileSystem_readFile(const char* fileName);

void fileSystem_free(File* file);

void fileSystem_print(const File* file);

#endif // FILE_SYSTEM_H