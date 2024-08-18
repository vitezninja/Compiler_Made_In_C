#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *substring(const char *string, int start, int end);

char convertEscapeString(const char *input);

#endif