#include "vm.h"

/*****************************************************************************************************
                            PRIVATE MY_STRING FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/* Inital token capacity for lexing */
#define INITIAL_TOKEN_CAPACITY 100

/**
 * Represents a collection of flags and options for configuring the compiler.
 * 
 * The `Flags` structure holds various settings and options specified by the user
 * through command-line arguments. It includes the following fields:
 * 
 * - `help`: Indicates if help information should be displayed.
 *           - 1 if help is requested (e.g., `-h` flag).
 *           - 0 otherwise.
 * 
 * - `onlyLex`: Indicates whether only lexical analysis should be performed.
 *              - 1 if only lexical analysis is requested (e.g., `-l` flag).
 *              - 0 otherwise.
 * 
 * - `noLink`: Indicates whether compilation only should be performed.
 * 
 * - `files`: An array of strings representing the source files to be compiled.
 * 
 * - `fileCount`: The number of source files specified in the `files` array.
 * 
 * - `isOutputFile`: Indicates whether an output file has been specified.
 *                   - 1 if an output file is specified (e.g., `-o` flag).
 *                   - 0 otherwise.
 * 
 * - `outputFile`: A string representing the name or path of the output file, if specified.
 * 
 * - `warnAll`: Indicates if all warnings should be enabled.
 *              - 1 if all warnings are enabled (e.g., `-Wall` flag).
 *              - 0 otherwise.
 * 
 * - `warnErrors`: Indicates if warnings should be treated as errors.
 *                 - 1 if warnings are treated as errors (e.g., `-Werror` flag).
 *                 - 0 otherwise.
 * 
 * - `debugInfo`: Indicates if debugging information should be included.
 *                - 1 if debugging information is included (e.g., `-g` flag).
 *                - 0 otherwise.
 * 
 * - `optimization`: Indicates if optimization should be enabled.
 *                   - 1 if optimization is enabled (e.g., `-O` flag).
 *                   - 0 otherwise.
 * 
 * - `headerFiles`: An array of strings representing header file paths specified by the user.
 * 
 * - `headerCount`: The number of header files specified in the `headerFiles` array.
 *
 * The `Flags` structure is used by various functions to manage the state and configuration of the compiler based on user input.
 * 
 * @note The caller is responsible for managing the lifecycle of the `Flags` object. After use, the memory allocated for the
 *       `Flags` structure, including its dynamic arrays, should be released using the `freeFlags` function.
 */
typedef struct flags
{
    int help;                /** Flag to indicate if help is requested. */
    int onlyLex;             /** Flag to indicate lexical analysis only. */
    int noLink;              /** Flag to indicate compilation only. */
    char **files;            /** Array of strings representing source files to compile. */
    size_t fileCount;        /** Number of source files. */
    int isOutputFile;        /** Flag to indicate if an output file is specified. */
    char *outputFile;        /** Name or path of the output file, if specified. */
    int warnAll;             /** Flag to enable all warnings. */
    int warnErrors;          /** Flag to treat warnings as errors. */
    int debugInfo;           /** Flag to include debugging information. */
    int optimization;        /** Flag to enable optimization. */
    char **headerFiles;      /** Array of strings representing header file paths. */
    size_t headerCount;      /** Number of header files. */
} Flags;

static int getFileSize(FILE *file);

static char *readFromFile(char *fileName);

static char **readFromFiles(char **fileNames, const size_t fileCount);

static void freeFileContent(char *fileContent);

static void freeFileContents(char **fileContents, const size_t fileCount);

static Flags *parseArgs(int argc, char **argv);

static void freeFlags(Flags *flags);

static void printUsage();

static void printHelp();

static Token **lexFile(const char *const fileContents, size_t *tokenCount);

static ASTNode *parseTokens(Token **tokens, size_t tokenCount);

static ASTNode *validateAST(ASTNode *node);

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
static int getFileSize(FILE *file)
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
static char *readFromFile(char *fileName)
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

/**
 * Reads the contents of multiple files into an array of strings.
 *
 * The `readFromFiles` function takes an array of file names, reads the contents of 
 * each file, and stores them in an array of strings. Each string in the returned array 
 * corresponds to the contents of one file.
 *
 * @param fileNames An array of `char*` representing the file names to read from. 
 *                  The array should contain `fileCount` elements.
 * @param fileCount The number of files to read, i.e., the size of the `fileNames` array.
 *
 * @return An array of `char*` where each element contains the contents of a corresponding file.
 *         Returns `NULL` if the `fileNames` array is `NULL` or if memory allocation fails.
 * 
 * @note The caller is responsible for freeing the memory allocated for the file contents 
 *       using `freeFileContents`. If a file cannot be read, the corresponding 
 *       entry in the returned array may be `NULL`.
 */
static char **readFromFiles(char **fileNames, const size_t fileCount)
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

/**
 * Frees the memory allocated for the contents of single file.
 *
 * The `freeFileContent` function deallocates the memory used to store the contents 
 * of a single file.
 *
 * @param fileContent A pointer to a `char` array representing the contents of a file.
 *
 * @note If `fileContent` is `NULL`, the function does nothing and logs an error 
 *       message to `stderr`. The caller should ensure `fileContent` is properly 
 *       allocated before passing it to this function.
 */
static void freeFileContent(char *fileContent)
{
    if (fileContent == NULL)
    {
        fprintf(stderr, "File content is NULL!\n");
        return;
    }

    free(fileContent);
}

/**
 * Frees the memory allocated for the contents of multiple files.
 *
 * The `freeFileContents` function deallocates the memory used to store the contents 
 * of multiple files, as well as the memory used for the array holding those contents.
 *
 * @param fileContents An array of `char*` where each element points to the contents 
 *                     of a file. The array should contain `fileCount` elements.
 * @param fileCount The number of files, i.e., the number of elements in the 
 *                  `FileContents` array.
 *
 * @note If `FileContents` is `NULL`, the function does nothing and logs an error 
 *       message to `stderr`. The caller should ensure `fileContents` is properly 
 *       allocated before passing it to this function.
 */
void freeFileContents(char **fileContents, const size_t fileCount)
{
    if (fileContents == NULL)
    {
        fprintf(stderr, "File contents array is null!\n");
        return;
    }

    for (size_t i = 0; i < fileCount; i++)
    {
        freeFileContent(fileContents[i]);
    }
    free(fileContents);
}

/**
 * Parses and handles command-line arguments to initialize and configure the `Flags` structure.
 * 
 * This function processes the command-line arguments (`argc` and `argv`) to set various flags and
 * options within a newly allocated `Flags` structure. It dynamically allocates memory for the
 * `Flags` structure and its members, based on the provided arguments.
 * 
 * The function identifies different flags (e.g., `-l`, `-h`, `-o`, etc.) and options (e.g., file paths,
 * macros, library paths) and populates the corresponding fields in the `Flags` structure. It also
 * performs error handling for invalid or unsupported arguments, and if any memory allocation fails,
 * it cleans up and returns `NULL`.
 * 
 * @param argc The number of command-line arguments.
 * 
 * @param argv An array of pointers to the command-line argument strings.
 * 
 * @return A pointer to a dynamically allocated `Flags` structure containing the parsed command-line options,
 *         or `NULL` if an error occurs (such as invalid arguments or memory allocation failures).
 * 
 * @note The caller is responsible for freeing the returned `Flags` structure and its associated memory
 *       using `freeFlags` when it is no longer needed.
 */
static Flags *parseArgs(int argc, char **argv)
{
    if (argv == NULL)
    {
        fprintf(stderr, "Arguments array is NULL!\n");
        return NULL;
    }

    if (argc < 2)
    {
        printUsage();
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
            if (strcmp(argv[i], "-h") == 0)
            {
                flags->help = 1;
            }
            else if (strcmp(argv[i], "-l") == 0)
            {
                flags->onlyLex = 1;
            }
            else if (strcmp(argv[i], "-c") == 0)
            {
                flags->noLink = 1;
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
                if (strncmp(argv[i], "-I", 2) == 0)
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

    if (flags->fileCount == 0 && !flags->help)
    {
        fprintf(stderr, "No files to compile!\n");
        freeFlags(flags);
        return NULL;
    }

    return flags;
}

/**
 * Frees memory associated with a `Flags` structure and its dynamically allocated members.
 * 
 * This function deallocates all memory allocated for the `Flags` structure, including any
 * dynamically allocated arrays and strings within the structure. If the `flags` pointer is `NULL`,
 * an error message is printed and the function returns immediately.
 * 
 * The function checks each dynamically allocated member of the `Flags` structure and frees it
 * appropriately. The `flags` structure itself is also freed at the end.
 * 
 * @param flags A pointer to the `Flags` structure to be freed. It is assumed to be dynamically allocated.
 * 
 * @note This function checks if the `flags` pointer is `NULL` before attempting to free its members.
 *       It also checks for each dynamically allocated member array to ensure it is not `NULL` before freeing.
 * 
 * @note After calling this function, the pointer to the `Flags` structure should not be used unless
 *       it is re-initialized, as the memory it points to will be deallocated.
 */
static void freeFlags(Flags *flags)
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

    free(flags);
}

/**
 * Prints the usage information for the program.
 *
 * This function displays a message indicating the correct usage of the program,
 * including the program name and the command-line options that can be specified
 * when running the program. The usage message format is dependent on the operating 
 * system being used.
 *
 * The usage message is formatted differently for Windows and Unix-like operating 
 * systems:
 *
 * - For Windows:
 *   Prints "Usage: cmc.exe [options] file..."
 * 
 * - For Linux/Unix-like systems:
 *   Prints "Usage: cmc [options] file..."
 *
 * If the platform is unknown or unsupported, a compilation error will occur.
 *
 * This function is typically called to show the user how to run the program when 
 * they provide incorrect arguments or request usage information.
 */
static void printUsage()
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    printf("Usage: cmc.exe [options] file...\n");
    #elif defined(__linux__) || defined(__unix__) || defined(_POSIX_VERSION)
    printf("Usage: cmc [options] file...\n");
    #else
    #error "Unknown compiler"
    #endif
}

/**
 * Prints the usage information and available command-line options.
 *
 * This function provides a help message to the user, detailing the various 
 * command-line options that can be used with the program. It is typically 
 * called when the user requests help (e.g., using the `-h` option).
 *
 * The options printed by this function include:
 *
 * - `-h`: 
 *    Prints this help message.
 *
 * - `-l`: 
 *    Only lex the input and print the tokens. This option is useful for 
 *    checking the lexical structure of the input file without compiling it.
 *
 * - `-c`: 
 *    Compiles the source files without linking. Generates object files 
 *    but does not produce an executable.
 *
 * - `-o <output_file>`: 
 *    Specifies the output file name. The user can define the name of 
 *    the output file, whether it be an executable or an object file.
 *
 * - `-Wall`: 
 *    Enables all compiler warnings, helping to identify potential issues 
 *    in the code.
 *
 * - `-Werror`: 
 *    Treats all warnings as errors. This means that any warning will 
 *    cause the compilation to fail.
 *
 * - `-g`: 
 *    Includes debugging information in the compiled output. This is 
 *    essential for debugging purposes.
 *
 * - `-O`: 
 *    Enables optimization during compilation, which can improve the 
 *    performance of the generated code.
 *
 * - `-I<path>`: 
 *    Adds a directory to the header file search path. This is useful 
 *    when your code depends on headers located in non-standard directories.
 *
 * - `-L<path>`: 
 *    Adds a directory to the library file search path. This helps the 
 *    linker find libraries that are not in standard locations.
 *
 * - `-D<macro>`: 
 *    Defines a macro for use in the code. This can be used to conditionally 
 *    include code or define constants.
 *
 * - `-std=<standard>`: 
 *    Specifies the C standard to use during compilation (e.g., `-std=c99`).
 */
static void printHelp()
{
    printUsage();
    printf("Options:\n");
    printf("  -h \t\t\tPrint this help message\n");
    printf("  -l \t\tOnly lex the input and print the tokens\n");
    printf("  -c \t\tCompiles the source files without linking.\n");
    printf("  -o <output_file> \tSpecify the output file\n");
    printf("  -Wall \t\tEnable all warnings\n");
    printf("  -Werror \t\tTreat warnings as errors\n");
    printf("  -g \t\t\tInclude debugging information\n");
    printf("  -O \t\t\tEnable optimization\n");
    printf("  -I<path> \t\tAdd a directory to the header file search path\n");
}

/**
 * Lexes the contents of a file into an array of tokens.
 *
 * The `lexFile` function takes the contents of a file as input and processes it to produce 
 * an array of tokens. These tokens represent the lexical elements of the input file, 
 * such as keywords, operators, identifiers, literals, etc.
 *
 * The function dynamically allocates memory for the array of tokens and returns a pointer 
 * to the array. The caller is responsible for freeing the memory using a suitable 
 * function after use.
 *
 * @param fileContents A constant pointer to a character array containing the contents of the file
 *                     to be lexed. This parameter must not be `NULL`.
 * 
 * @param tokenCount   A pointer to a `size_t` variable where the function will store the number 
 *                     of tokens generated from the input file. The value is set to `0` if 
 *                     lexing fails or if there are no tokens.
 *
 * @return A pointer to an array of `Token` pointers representing the tokens parsed from the input file.
 *         Returns `NULL` if there is an error during lexing, such as memory allocation failure,
 *         invalid input, or errors encountered while parsing.
 */
static Token **lexFile(const char *const fileContents, size_t *tokenCount)
{
    if (fileContents == NULL)
    {
        fprintf(stderr, "File contents is NULL!\n");
        return NULL;
    }

    //Create the tokens array
    size_t tokenCapacity = INITIAL_TOKEN_CAPACITY;
    Token **tokens = malloc(tokenCapacity * sizeof(Token));
    if (tokens == NULL)
    {
        fprintf(stderr, "Memory allocation for Tokens failed!\n");
        return NULL;
    }
    *tokenCount = 0;

    //Create the lexer
    Lexer *lexer = createLexer(fileContents);
    if (lexer == NULL)
    {
        fprintf(stderr, "Failed to create Lexer.\n");
        free(tokens);
        return NULL;
    }

    //Lex the input
    while (1)
    {
        Token *ctoken = lex(lexer);
        if (ctoken == NULL)
        {
            fprintf(stderr, "Error lexing input or end of input.\n");
            deleteTokens(tokens, *tokenCount);
            deleteLexer(lexer);
            return NULL;
        }

        if (*tokenCount >= tokenCapacity)
        {
            tokenCapacity *= 2;
            Token **newTokens = realloc(tokens, tokenCapacity * sizeof(Token *));
            if (newTokens == NULL)
            {
                fprintf(stderr, "Memory allocation for tokens array failed!\n");
                deleteTokens(tokens, *tokenCount);
                deleteLexer(lexer);
                return NULL;
            }
            tokens = newTokens;
        }

        tokens[(*tokenCount)++] = ctoken;

        if (ctoken->type == TOKEN_EOF)
        {
            break;
        }
    }

    //If lexer had errors, print them and return
    if (lexer->errorCount > 0)
    {
        fprintf(stderr, "Lexing failed!\n");
        for (size_t i = 0; i < lexer->errorCount; i++)
        {
            printError(lexer->errors[i]);
        }
        
        deleteTokens(tokens, *tokenCount);
        deleteLexer(lexer);
        return NULL;
    }

    deleteLexer(lexer);
    return tokens;
}

/**
 * Parses an array of tokens into an Abstract Syntax Tree (AST).
 *
 * The `parseTokens` function takes an array of tokens generated by a lexer and 
 * processes them to construct an Abstract Syntax Tree (AST) representing the 
 * syntactic structure of the input source code. The function dynamically 
 * allocates memory for the AST and returns a pointer to its root node.
 *
 * The caller is responsible for freeing the memory associated with the returned 
 * AST node and its children using a suitable function after use.
 *
 * @param tokens     A pointer to an array of `Token` pointers representing the 
 *                   lexical tokens to be parsed. This parameter must not be `NULL`.
 * 
 * @param tokenCount The number of tokens in the `tokens` array.
 *
 * @return A pointer to the root node of the constructed AST. 
 *         Returns `NULL` if there is an error during parsing, such as memory allocation 
 *         failure, invalid input, or syntax errors in the tokens.
 */
static ASTNode *parseTokens(Token **tokens, size_t tokenCount)
{
    if (tokens == NULL)
    {
        fprintf(stderr, "Tokens array is NULL!\n");
        deleteTokens(tokens, tokenCount);
        return NULL;
    }

    //Create the parser
    Parser *parser = createParser(tokens, tokenCount);
    if (parser == NULL)
    {
        fprintf(stderr, "Failed to create Parser.\n");
        deleteTokens(tokens, tokenCount);
        return NULL;
    }

    //Parse the tokens
    int success = parse(parser);
    if (!success)
    {
        fprintf(stderr, "Parsing failed!\n");
        for (size_t i = 0; i < parser->errorCount; i++)
        {
            printError(parser->errors[i]);
        }

        deleteParser(parser);
        deleteTokens(tokens, tokenCount);
        return NULL;
    }

    if (parser->errorCount > 0)
    {
        fprintf(stderr, "Parsing completed with errors!\n");
        for (size_t i = 0; i < parser->errorCount; i++)
        {
            printError(parser->errors[i]);
        }
        deleteParser(parser);
        deleteTokens(tokens, tokenCount);
        return NULL;
    }

    //Get the AST root
    ASTNode *root = getCopyAST(parser);
    deleteParser(parser);

    return root;
}

static ASTNode *validateAST(ASTNode *node)
{
    if (node == NULL)
    {
        printf("Node is NULL!\n");
        return NULL;
    }

    Validator *validator = createValidator(node);
    int success = validate(validator);
    if (!success)
    {
        fprintf(stderr, "Validation failed!\n");
        for (size_t i = 0; i < validator->errorCount; i++)
        {
            printError(validator->errors[i]);
        }

        deleteValidator(validator);
        return NULL;
    }

    if (validator->errorCount > 0)
    {
        fprintf(stderr, "Validation completed with errors!\n");
        for (size_t i = 0; i < validator->errorCount; i++)
        {
            printError(validator->errors[i]);
        }
        deleteValidator(validator);
        return NULL;
    }

    ASTNode *validated = copyASTNode(validator);
    deleteValidator(validator);

    return validated;
}

/*****************************************************************************************************
                                PUBLIC MY_STRING FUNCTIONS START HERE                                
 *****************************************************************************************************/

int runVM(int argc, char **argv)
{
    //Parse arguments
    Flags *flags = parseArgs(argc, argv);
    if (flags == NULL)
    {
        return -1;
    }

    //Handle arguments
    if (flags->help)
    {
        printHelp(argv[0]);
        freeFlags(flags);
        return 0;
    }

    //Read the contents of the files
    char **fileContents = readFromFiles(flags->files, flags->fileCount);
    //TODO:
    //Handle multiple files, we only handle one file for now
    const char *const input = fileContents[0];

    //Lex the input
    size_t tokenCount = 0;
    Token **tokens = lexFile(input, &tokenCount);
    if (tokens == NULL)
    {
        freeFileContents(fileContents, flags->fileCount);
        freeFlags(flags);
        return -1;
    }

    //If only lexing is requested, print the tokens and return
    if (flags->onlyLex)
    {
        for (size_t i = 0; i < tokenCount; i++)
        {
            if (tokens[i]->type != TOKEN_WHITESPACE && tokens[i]->type != TOKEN_LINE_COMMENT && tokens[i]->type != TOKEN_BLOCK_COMMENT)
            {
                printToken(tokens[i]);
            }
        }

        freeFileContents(fileContents, flags->fileCount);
        freeFlags(flags);
        deleteTokens(tokens, tokenCount);
        return 0;
    }

    //Free the file contents as they are extracted into tokens
    //This needs to change if we want to support multiple files
    freeFileContents(fileContents, flags->fileCount);

    //Parse the tokens
    ASTNode *root = parseTokens(tokens, tokenCount);
    if (root == NULL)
    {
        freeFlags(flags);
        return -1;
    }

    //Print the AST
    printf("\n\nParsed AST:\n");
    printASTNode(root, "", 0);

    //Validate the AST
    ASTNode *validated = validateAST(root);
    if (validated == NULL)
    {
        freeFlags(flags);
        deleteTokens(tokens, tokenCount);
        deleteASTNode(root);
        return -1;
    }

    //Print the validated AST
    printf("\n\nValidated AST:\n");
    printASTNode(validated, "", 0);

    //TODO:
    //Do things with the AST

    //Free memory
    freeFlags(flags);
    deleteASTNode(validated);
    deleteTokens(tokens, tokenCount);
    return 0;
}