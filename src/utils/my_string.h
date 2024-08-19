#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *substring(const char *const string, const int start, const int end);

char convertEscapeString(const char *const input);

#endif