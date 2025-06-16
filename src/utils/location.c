#include "utils/location.h"

void sourceLocation_print(const SourceLocation *location)
{
    if (location == NULL)
    {
        DEBUG_PRINT("sourceLocation_print: location is NULL\n");
        return;
    }

    printf("SourceLocation {\n");
    printf("    File Name   : %s\n", location->fileName);
    printf("    Line        : %" PRIu32 "\n", location->line);
    printf("    Column      : %" PRIu32 "\n", location->column);
    printf("    Line Start  : %" PRIu32 "\n", location->lineStart);
    printf("}\n");
}