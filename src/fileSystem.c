#include "fileSystem.h"

File fileSystem_readFile(const char* fileName)
{
    if (fileName == NULL)
    {
        DEBUG_PRINT("fileSystem_readFile: fileName is NULL\n");
        return (File){0};
    }

    FILE* file = fopen(fileName, "rb");
    if (file == NULL)
    {
        if (errno == ENOENT)
        {
            DEBUG_PRINT("fileSystem_readFile: File '%s' does not exist\n", fileName);
        }
        else if (errno == EACCES)
        {
            DEBUG_PRINT("fileSystem_readFile: Permission denied for file '%s'\n", fileName);
        }
        else
        {
            DEBUG_PRINT("fileSystem_readFile: Could not open file '%s': %d\n", fileName, errno);
        }

        return (File){0};
    }

    if (fseek(file, 0, SEEK_END) != 0)
    {
        fclose(file);
        DEBUG_PRINT("fileSystem_readFile: fseek failed with errno %d\n", errno);
        return (File){0};
    }

    size_t fileSize = ftell(file);
    if (errno != 0)
    {
        fclose(file);
        DEBUG_PRINT("fileSystem_readFile: ftell failed with errno %d\n", errno);
        return (File){0};
    }

    if (fseek(file, 0, SEEK_SET) != 0)
    {
        fclose(file);
        DEBUG_PRINT("fileSystem_readFile: fseek to start failed with errno %d\n", errno);
        return (File){0};
    }

    if (fileSize == 0)
    {
        fclose(file);
        DEBUG_PRINT("fileSystem_readFile: File '%s' is empty\n", fileName);
        return (File){0};
    }

    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL)
    {
        fclose(file);
        DEBUG_PRINT("fileSystem_readFile: Memory allocation failed for file '%s': %d\n", fileName, errno);
        return (File){0};
    }
    size_t bytesRead = fread(buffer, 1, fileSize, file);
    fclose(file);
    if (bytesRead != fileSize)
    {
        free(buffer);
        if (errno == EIO)
        {
            DEBUG_PRINT("fileSystem_readFile: I/O error while reading file '%s': %d\n", fileName, errno);
        }
        else
        {
            DEBUG_PRINT("fileSystem_readFile: fread failed for file '%s': %d\n", fileName, errno);
        }
        return (File){0};
    }

    buffer[bytesRead] = '\0';
    return (File){ .name = fileName, .sourceBuffer = buffer, .sourceBufferSize = bytesRead };
}

void fileSystem_free(File* file)
{
    if (file == NULL)
    {
        DEBUG_PRINT("fileSystem_free: file is NULL\n");
        return;
    }
    free((char *)file->sourceBuffer);
}

void fileSystem_print(const File* file)
{
    if (file == NULL)
    {
        DEBUG_PRINT("fileSystem_print: file is NULL\n");
        return;
    }

    printf("File {\n");
    printf("    Name: %s\n", file->name);
    printf("    Size: %zu bytes\n", file->sourceBufferSize);
    printf("    Content:\n%s\n", file->sourceBuffer);
    printf("}\n");
}