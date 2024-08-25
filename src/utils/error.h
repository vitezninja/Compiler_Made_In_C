#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include "token.h"

typedef enum errorType
{
    ERROR_NONE,
    ERROR_LEXING,
    ERROR_PARSING,
} ErrorType;

typedef struct error
{
    ErrorType type;
    const char *message;
    const Token *errorToken;
} Error;

Error *createError(const ErrorType type, const char *const message, const Token *const token);

void deleteError(Error *error);

void deleteErrors(Error **errors, const size_t count);

void printError(const Error *const error);

#endif