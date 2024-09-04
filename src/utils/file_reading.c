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

Flags *parseArgs(int argc, char **argv)
{
    if (argv == NULL)
    {
        fprintf(stderr, "Arguments array is NULL!\n");
        return NULL;
    }

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <path_to_file_to_compile>\n", argv[0]);
        return NULL;
    }

    Flags *flags = malloc(sizeof(Flags));
    if (flags == NULL)
    {
        fprintf(stderr, "Memory allocation for Flags failed!\n");
        return NULL;
    }
    flags->onlyLex = 0;
    flags->help = 0;
    flags->files = malloc(sizeof(char *));
    if (flags->files == NULL)
    {
        fprintf(stderr, "Memory allocation for files failed!\n");
        free(flags);
        return NULL;
    }
    flags->fileCount = 0;
    flags->isOutputFile = 0;
    flags->outputFile = NULL;
    flags->warnAll = 0;
    flags->warnErrors = 0;
    flags->debugInfo = 0;
    flags->optimization = 0;
    flags->headerFiles = malloc(sizeof(char *));
    if (flags->headerFiles == NULL)
    {
        fprintf(stderr, "Memory allocation for header files failed!\n");
        freeFlags(flags);
        return NULL;
    }
    flags->headerCount = 0;
    flags->libraryFiles = malloc(sizeof(char *));
    if (flags->libraryFiles == NULL)
    {
        fprintf(stderr, "Memory allocation for library files failed!\n");
        freeFlags(flags);
        return NULL;
    }
    flags->libraryCount = 0;
    flags->macros = malloc(sizeof(char *));
    if (flags->macros == NULL)
    {
        fprintf(stderr, "Memory allocation for macros failed!\n");
        freeFlags(flags);
        return NULL;
    }
    flags->macroCount = 0;
    flags->standard = NULL;

    for (size_t i = 1; (int)i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            flags->files[flags->fileCount++] = argv[i];
            char **newFiles = realloc(flags->files, flags->fileCount * sizeof(char *));
            if (newFiles == NULL)
            {
                fprintf(stderr, "Memory reallocation for files failed!\n");
                freeFlags(flags);
                return NULL;
            }
            flags->files = newFiles;
        }
        else
        {
            if (strcmp(argv[i], "-l") == 0)
            {
                flags->onlyLex = 1;
            }
            else if (strcmp(argv[i], "-h") == 0)
            {
                flags->help = 1;
            }
            else if (strcmp(argv[i], "-o") == 0)
            {
                flags->isOutputFile = 1;
                i++;
                flags->outputFile = argv[i];
            }
            else if (strcmp(argv[i], "-Wall") == 0)
            {
                flags->warnAll = 1;
            }
            else if (strcmp(argv[i], "-Werror") == 0)
            {
                flags->warnErrors = 1;
            }
            else if (strcmp(argv[i], "-g") == 0)
            {
                flags->debugInfo = 1;
            }
            else if (strcmp(argv[i], "-O") == 0)
            {
                flags->optimization = 1;
            }
            else if (strlen(argv[i]) > 2)
            {
                if (strncmp(argv[i], "-I.", 2) == 0)
                {
                    flags->headerFiles[flags->headerCount++] = substring(argv[i], 2, strlen(argv[i]));
                    char **newHeaderFiles = realloc(flags->headerFiles, flags->headerCount * sizeof(char *));
                    if (newHeaderFiles == NULL)
                    {
                        fprintf(stderr, "Memory reallocation for header files failed!\n");
                        freeFlags(flags);
                        return NULL;
                    }
                    flags->headerFiles = newHeaderFiles;
                }
                else if (strncmp(argv[i], "-L", 2) == 0)
                {
                    flags->libraryFiles[flags->libraryCount++] = substring(argv[i], 2, strlen(argv[i]));
                    char **newLibraryFiles = realloc(flags->libraryFiles, flags->libraryCount * sizeof(char *));
                    if (newLibraryFiles == NULL)
                    {
                        fprintf(stderr, "Memory reallocation for library files failed!\n");
                        freeFlags(flags);
                        return NULL;
                    }
                    flags->libraryFiles = newLibraryFiles;
                }
                else if (strncmp(argv[i], "-D", 2) == 0)
                {
                    flags->macros[flags->macroCount++] = substring(argv[i], 2, strlen(argv[i]));
                    char **newMacros = realloc(flags->macros, flags->macroCount * sizeof(char *));
                    if (newMacros == NULL)
                    {
                        fprintf(stderr, "Memory reallocation for macros failed!\n");
                        freeFlags(flags);
                        return NULL;
                    }
                    flags->macros = newMacros;
                }
                else if (strncmp(argv[i], "-std=", 5) == 0)
                {
                    flags->standard = substring(argv[i], 5, strlen(argv[i]));
                }
                else
                {
                    fprintf(stderr, "Invalid argument %s!\n", argv[i]);
                    freeFlags(flags);
                    return NULL;
                }
            }
            else
            {
                fprintf(stderr, "Invalid argument %s!\n", argv[i]);
                freeFlags(flags);
                return NULL;
            }
        }
    }

    return flags;
}

void freeFlags(Flags *flags)
{
    if (flags == NULL)
    {
        fprintf(stderr, "Flags are NULL!\n");
        return;
    }

    if (flags->files != NULL)
    {
        free(flags->files);
    }

    if (flags->headerFiles != NULL)
    {
        for (size_t i = 0; i < flags->headerCount; i++)
        {
            free(flags->headerFiles[i]);
        }
        free(flags->headerFiles);
    }

    if (flags->libraryFiles != NULL)
    {
        for (size_t i = 0; i < flags->libraryCount; i++)
        {
            free(flags->libraryFiles[i]);
        }
        free(flags->libraryFiles);
    }

    if (flags->macros != NULL)
    {
        for (size_t i = 0; i < flags->macroCount; i++)
        {
            free(flags->macros[i]);
        }
        free(flags->macros);
    }

    free(flags);
}

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