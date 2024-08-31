#include "error.h"

/*****************************************************************************************************
                            PRIVATE MY_STRING FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/*****************************************************************************************************
                                PRIVATE MY_STRING FUNCTIONS START HERE
 *****************************************************************************************************/

/*****************************************************************************************************
                                PUBLIC MY_STRING FUNCTIONS START HERE                                
 *****************************************************************************************************/

Error *createError(const ErrorType type, const char *message, const Token *token)
{
    if (message == NULL)
    {
        fprintf(stderr, "The message is NULL!\n");
        return NULL;
    }

    Error *error = malloc(sizeof(Error));
    if (error == NULL)
    {
        fprintf(stderr, "Memory allocation for Error failed!\n");
        return NULL;
    }

    error->type = type;
    error->message = message;
    error->errorToken = token;

    return error;
}

void deleteError(Error *error)
{
    if (error == NULL)
    {
        return;
    }

    if (error->errorToken != NULL)
    {
        free((char *)error->errorToken);
    }

    free(error);
}

void deleteErrors(Error **errors, const size_t count)
{
    if (errors == NULL)
    {
        fprintf(stderr, "Errors array is NULL!\n");
        return;
    }

    for (size_t i = 0; i < count; i++)
    {
        deleteError(errors[i]);
    }
}

void printError(const Error *const error)
{
    if (error == NULL)
    {
        fprintf(stderr, "The error is NULL!\n");
        return;
    }

    if (error->message == NULL)
    {
        fprintf(stderr, "The message is NULL!\n");
        return;
    }

    printf("Error: %s\n", error->message);
    if (error->errorToken != NULL)
    {
        if (error->type == ERROR_PARSING)
        {
            printf("\t");
            printToken(error->errorToken);
            printf("\t\tfrom: %d to %d\n", error->errorToken->start, (int)(error->errorToken->start + error->errorToken->length));  
        }
        else
        {
            printf("\tfrom: %d to %d\n", error->errorToken->start, (int)(error->errorToken->start + error->errorToken->length));
        }
    }
}