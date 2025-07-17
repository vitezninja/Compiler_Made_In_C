#include "options.h"

Options options_create(int argc, char** argv)
{
    if (argc < 2)
    {
        DEBUG_PRINT("options_create: No input files provided.\n");
        return (Options){0};
    }

    if (argv == NULL)
    {
        DEBUG_PRINT("options_create: Argument vector is NULL.\n");
        return (Options){0};
    }

    Options options = {0};
    options.flags = (Bitset64){0};

    options.outputFile = NULL;
    options.files = malloc(sizeof(char *));
    if (options.files == NULL)
    {
        DEBUG_PRINT("options_create: Memory allocation failed for files: %d\n", errno);
        return (Options){0};
    }
    options.fileCount = 0;

    options.headerFiles = malloc(sizeof(char *));
    if (options.headerFiles == NULL)
    {
        free(options.files);
        DEBUG_PRINT("options_create: Memory allocation failed for header files: %d\n", errno);
        return (Options){0};
    }
    options.headerCount = 0;

    for (size_t i = 1; (int)i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            char **newFiles = realloc(options.files, (options.fileCount + 1) * sizeof(char *));
            if (newFiles == NULL)
            {
                free(options.files);
                free(options.headerFiles);
                DEBUG_PRINT("options_create: Memory reallocation failed for files: %d\n", errno);
                return (Options){0};
            }

            newFiles[options.fileCount] = argv[i];
            options.files = newFiles;
            options.fileCount++;
        }
        else
        {
            if (strcmp(argv[i], "-h") == 0)
            {
                bitset64_set(&(options.flags), OPTION_FLAG_HELP);
            }
            else if (strcmp(argv[i], "-c") == 0)
            {
                bitset64_set(&(options.flags), OPTION_FLAG_NO_LINK);
            }
            else if (strcmp(argv[i], "-o") == 0)
            {
                if (i + 1 >= (size_t)argc)
                {
                    free(options.files);
                    free(options.headerFiles);

                    DEBUG_PRINT("options_create: Missing output file after -o option.\n");
                    return (Options){0};
                }
                bitset64_set(&(options.flags), OPTION_FLAG_IS_OUTPUT_FILE);
                i++;
                options.outputFile = argv[i];
            }
            else if (strcmp(argv[i], "-Wall") == 0)
            {
                bitset64_set(&(options.flags), OPTION_FLAG_WARN_ALL);
            }
            else if (strcmp(argv[i], "-Werror") == 0)
            {
                bitset64_set(&(options.flags), OPTION_FLAG_WARN_ERRORS);
            }
            else if (strcmp(argv[i], "-g") == 0)
            {
                bitset64_set(&(options.flags), OPTION_FLAG_DEBUG_INFO);
            }
            else if (strcmp(argv[i], "-O") == 0)
            {
                bitset64_set(&(options.flags), OPTION_FLAG_OPTIMIZATION);
            }
            else if (strlen(argv[i]) > 2)
            {
                if (strncmp(argv[i], "-I", 2) == 0)
                {
                    char **newHeaderFiles = realloc(options.headerFiles, (options.headerCount + 1) * sizeof(char *));
                    if (newHeaderFiles == NULL)
                    {
                        free(options.files);
                        free(options.headerFiles);
                        DEBUG_PRINT("options_create: Memory reallocation failed for header files: %d\n", errno);
                        return (Options){0};
                    }

                    newHeaderFiles[options.headerCount] = argv[i] + 2;
                    options.headerFiles = newHeaderFiles;
                    options.headerCount++;
                }
                else
                {
                    free(options.files);
                    free(options.headerFiles);
                    DEBUG_PRINT("options_create: Invalid argument %s!\n", argv[i]);
                    return (Options){0};
                }
            }
            else
            {
                free(options.files);
                free(options.headerFiles);
                DEBUG_PRINT("options_create: Invalid argument %s!\n", argv[i]);
                return (Options){0};
            }
        }
    }

    if (bitset64_isEmpty(&(options.flags)))
    {
        bitset64_set(&(options.flags), OPTION_FLAG_NONE);
    }
    return options;
}

void options_free(Options *options)
{
    if (options == NULL)
    {
        DEBUG_PRINT("options_free: Options structure is NULL.\n");
        return;
    }
    free(options->files);
    free(options->headerFiles);
}

void options_print(const Options *options)
{
    if (options == NULL)
    {
        DEBUG_PRINT("options_print: Options structure is NULL.\n");
        return;
    }

    printf("Options {\n");
    printf("\tFlags:\n");
    if (bitset64_test(&(options->flags), OPTION_FLAG_NONE))
    {
        printf("\t\t- None\n");
    }
    if (bitset64_test(&(options->flags), OPTION_FLAG_HELP))
    {
        printf("\t\t- Help\n");
    }
    if (bitset64_test(&(options->flags), OPTION_FLAG_NO_LINK))
    {
        printf("\t\t- No Link\n");
    }
    if (bitset64_test(&(options->flags), OPTION_FLAG_IS_OUTPUT_FILE))
    {
        printf("\t\t- Is Output File\n");
    }
    if (bitset64_test(&(options->flags), OPTION_FLAG_WARN_ALL))
    {
        printf("\t\t- Warn All\n");
    }
    if (bitset64_test(&(options->flags), OPTION_FLAG_WARN_ERRORS))
    {
        printf("\t\t- Warn Errors\n");
    }
    if (bitset64_test(&(options->flags), OPTION_FLAG_DEBUG_INFO))
    {
        printf("\t\t- Debug Info\n");
    }
    if (bitset64_test(&(options->flags), OPTION_FLAG_OPTIMIZATION))
    {
        printf("\t\t- Optimization\n");
    }
    printf("\tOutput File: %s\n", options->outputFile ? options->outputFile : "None");
    printf("\tFile Count: %zu\n", options->fileCount);
    printf("\tFiles:\n");
    if (options->fileCount == 0)
    {
        printf("\t\t- None\n");
    }
    else
    {
        for (size_t i = 0; i < options->fileCount; i++)
        {
            printf("\t\t- %s\n", options->files[i]);
        }
    }
    printf("\tHeader Count: %zu\n", options->headerCount);
    printf("\tHeader Files:\n");
    if (options->headerCount == 0)
    {
        printf("\t\t- None\n");
    }
    else
    {
        for (size_t i = 0; i < options->headerCount; i++)
        {
            printf("\t\t- %s\n", options->headerFiles[i]);
        }
    }
    printf("}\n");
}

bool options_tryPrintHelp(const Options *options)
{
    if (options == NULL)
    {
        DEBUG_PRINT("options_tryPrintHelp: Options structure is NULL.\n");
        return false;
    }

    if (!bitset64_test(&(options->flags), OPTION_FLAG_HELP))
    {
        return false;
    }

    printf("Usage: cmc [options] <source files>\n");
    printf("Options:\n");
    printf("  -h \t\t\tPrint this help message\n");
    printf("  -c \t\t\tCompiles the source files without linking.\n");
    printf("  -o <output_file> \tSpecify the output file\n");
    printf("  -Wall \t\tEnable all warnings\n");
    printf("  -Werror \t\tTreat warnings as errors\n");
    printf("  -g \t\t\tInclude debugging information\n");
    printf("  -O \t\t\tEnable optimization\n");
    printf("  -I<path> \t\tAdd a directory to the header file search path\n");
    printf("  <source files> \tList of source files to compile\n");
    printf("\n");
    return true;
}