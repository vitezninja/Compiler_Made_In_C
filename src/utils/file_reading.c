#include "file_reading.h"

/*****************************************************************************************************
                            PRIVATE MY_STRING FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

int getFileSize(FILE *file);

char *readFromFile(char *fileName);

/*****************************************************************************************************
                                PRIVATE MY_STRING FUNCTIONS START HERE
 *****************************************************************************************************/

int getFileSize(FILE *file)
{
    if (file == NULL)
    {
        fprintf(stderr, "File is NULL!\n");
        return -1;
    }

    if (ftell(file) != 0)
    {
        fprintf(stderr, "The file wasn't opened at the start or was already modifyed.\n");
        return -1;
    }
    fseek(file, 0, SEEK_END);

    int size = ftell(file) / sizeof(char);
    if (size == 0)
    {
        fprintf(stderr, "The file was empty!\n");
        return -1;
    }

    fseek(file, 0, SEEK_SET);

    return size;
}

char *readFromFile(char *fileName)
{
    if (fileName == NULL)
    {
        fprintf(stderr, "File name is NULL!\n");
        return NULL;
    }

    FILE *file = fopen(fileName, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file %s!\n", fileName);
        return NULL;
    }

    int size = getFileSize(file);
    if (size == -1)
    {
        fclose(file);
        return NULL;
    }

    char *content = malloc(size + 1 * sizeof(char));

    if ((int)fread(content, sizeof(char), size, file) != size)
    {
        fprintf(stderr, "Failed reading from the file %s!\n", fileName);
        free(content);
        fclose(file);
        return NULL;
    }

    content[size] = '\0';
    fclose(file);
    return content;
}


/*****************************************************************************************************
                                PUBLIC MY_STRING FUNCTIONS START HERE                                
 *****************************************************************************************************/

char **readFromFiles(char **fileNames, const size_t fileCount)
{
    if (fileNames == NULL)
    {
        fprintf(stderr, "File name array is null!\n");
        return NULL;
    }

    char **fileContents = malloc(fileCount * sizeof(char *));
    for (size_t i = 0; i < fileCount; i++)
    {
        fileContents[i] = readFromFile(fileNames[i]);
    }
    
    return fileContents;
}

void freeFileContent(char **FileContents, const size_t fileCount)
{
    if (FileContents == NULL)
    {
        fprintf(stderr, "File contents array is null!\n");
        return;
    }

    for (size_t i = 0; i < fileCount; i++)
    {
        free(FileContents[i]);
    }
    free(FileContents);
}