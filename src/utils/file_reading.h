#ifndef FILE_READING_H
#define FILE_READING_H

#include <stdio.h>
#include <stdlib.h>

char **readFromFiles(char **fileNames, const size_t fileCount);

void freeFileContent(char **FileContents, const size_t fileCount);

#endif