#include "file_reading.h"

/*****************************************************************************************************
                            PRIVATE MY_STRING FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

int getFileSize(FILE *file);

char *readFromFile(char *fileName);

/*****************************************************************************************************
                                PRIVATE MY_STRING FUNCTIONS START HERE
 *****************************************************************************************************/

/**
 * Retrieves the size of a file in bytes.
 * 
 * The `getFileSize` function calculates the size of a file by seeking to the end 
 * of the file and determining the position of the file pointer, then returning 
 * the size in bytes.
 * 
 * @param file A pointer to the `FILE` object representing the open file. 
 *             The file must be opened in binary mode and positioned at the start.
 * 
 * @return The size of the file in bytes on success. 
 *         Returns -1 if the file pointer is `NULL`, if the file was not opened 
 *         at the start, if the file is empty, or if an error occurs.
 * 
 * @note The function assumes that the file is opened in binary mode. 
 *       The file pointer will be reset to the beginning of the file after 
 *       determining the size. Error messages are printed to `stderr` if any 
 *       issues are encountered.
 */
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

/**
 * Reads the contents of a file into a string.
 * 
 * The `readFromFile` function reads the contents of a file into a string, 
 * allocating memory for the string and returning a pointer to the string.
 * 
 * @param fileName A string containing the name of the file to read from.
 * 
 * @return A pointer to the string containing the file contents on success. 
 *         Returns `NULL` if the file name is `NULL`, if the file cannot be opened, 
 *         if the file cannot be read, or if memory allocation fails.
 * 
 * @note The function allocates memory for the string containing the file contents. 
 *       It is the caller's responsibility to free this memory when it is no longer needed by calling `freeFileContent`.
 */
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