#include "file_reader.h"

/*****************************************************************************************************
                            PRIVATE FILE_READER FUNCTIONS DECLARATIONS START HERE
 *****************************************************************************************************/

/*****************************************************************************************************
                                PRIVATE FILE_READER FUNCTIONS START HERE
 *****************************************************************************************************/

/*****************************************************************************************************
                                PUBLIC FILE_READER FUNCTIONS START HERE                                
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

char *readFromFile(const char *fileName)
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

char **readFromFiles(const char **fileNames, const size_t fileCount)
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

void freeFileContent(char *fileContent)
{
    if (fileContent == NULL)
    {
        fprintf(stderr, "File content is NULL!\n");
        return;
    }

    free(fileContent);
}

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

My_TokenType *readLexerFile(const char *fileName, size_t *tokenCount)
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

    My_TokenType *tokensTypes = malloc(100 * sizeof(My_TokenType));
    if (tokensTypes == NULL)
    {
        fprintf(stderr, "Memory allocation for tokensTypes failed!\n");
        fclose(file);
        return NULL;
    }
    *tokenCount = 0;

    while (1)
    {
        char c = fgetc(file);
        if (c == EOF)
        {
            break;
        }
        else if (c == '#')
        {
            while ((c = fgetc(file)) != '#')
            {
                if (c == EOF || c == '\\')
                {
                    free(tokensTypes);
                    return NULL;
                }
            }
            continue;
        }
        else if (c == '\\')
        {
            continue;
        }
        else if (c == '\n')
        {
            continue;
        }
        else if (c == '\r')
        {
            continue;
        }
        else if (c == ' ')
        {
            continue;
        }

        size_t i = 0;
        char *line = malloc(35 * sizeof(char));
        line[i++] = c;
        while ((c = fgetc(file)) != '\\')
        {
            if (c == EOF)
            {
                free(tokensTypes);
                return NULL;
            }
            line[i++] = c;
        }
        line[i - 1] = '\0';

        if (*tokenCount % 100 == 0)
        {
            tokensTypes = realloc(tokensTypes, (*tokenCount + 100) * sizeof(My_TokenType));
            if (tokensTypes == NULL)
            {
                fprintf(stderr, "Memory reallocation for tokensTypes failed!\n");
                fclose(file);
                return NULL;
            }
        }

        if (strcmp(line, "PLUS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_PLUS;
        }
        else if (strcmp(line, "DOUBLE_PLUS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_DOUBLE_PLUS;
        }
        else if (strcmp(line, "MINUS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_MINUS;
        }
        else if (strcmp(line, "DOUBLE_MINUS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_DOUBLE_MINUS;
        }
        else if (strcmp(line, "STAR") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_STAR;
        }
        else if (strcmp(line, "SLASH") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_SLASH;
        }
        else if (strcmp(line, "PERCENT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_PERCENT;
        }
        else if (strcmp(line, "PLUS_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_PLUS_EQUALS;
        }
        else if (strcmp(line, "MINUS_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_MINUS_EQUALS;
        }
        else if (strcmp(line, "STAR_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_STAR_EQUALS;
        }
        else if (strcmp(line, "SLASH_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_SLASH_EQUALS;
        }
        else if (strcmp(line, "PERCENT_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_PERCENT_EQUALS;
        }
        else if (strcmp(line, "BITWISE_LEFT_SHIFT_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_LEFT_SHIFT_EQUALS;
        }
        else if (strcmp(line, "BITWISE_RIGHT_SHIFT_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_RIGHT_SHIFT_EQUALS;
        }
        else if (strcmp(line, "BITWISE_AND_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_AND_EQUALS;
        }
        else if (strcmp(line, "BITWISE_XOR_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_XOR_EQUALS;
        }
        else if (strcmp(line, "BITWISE_OR_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_OR_EQUALS;
        }
        else if (strcmp(line, "EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_EQUALS;
        }
        else if (strcmp(line, "DOUBLE_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_DOUBLE_EQUALS;
        }
        else if (strcmp(line, "NOT_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_NOT_EQUALS;
        }
        else if (strcmp(line, "LESS_THAN") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_LESS_THAN;
        }
        else if (strcmp(line, "GREATER_THAN") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_GREATER_THAN;
        }
        else if (strcmp(line, "LESS_THAN_OR_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_LESS_THAN_OR_EQUALS;
        }
        else if (strcmp(line, "GREATER_THAN_OR_EQUALS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_GREATER_THAN_OR_EQUALS;
        }
        else if (strcmp(line, "AND") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_AND;
        }
        else if (strcmp(line, "OR") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_OR;
        }
        else if (strcmp(line, "NOT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_NOT;
        }
        else if (strcmp(line, "BITWISE_AND") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_AND;
        }
        else if (strcmp(line, "BITWISE_OR") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_OR;
        }
        else if (strcmp(line, "BITWISE_XOR") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_XOR;
        }
        else if (strcmp(line, "BITWISE_NOT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_NOT;
        }
        else if (strcmp(line, "BITWISE_LEFT_SHIFT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_LEFT_SHIFT;
        }
        else if (strcmp(line, "BITWISE_RIGHT_SHIFT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BITWISE_RIGHT_SHIFT;
        }
        else if (strcmp(line, "OPEN_PARENTHESIS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_OPEN_PARENTHESIS;
        }
        else if (strcmp(line, "CLOSE_PARENTHESIS") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_CLOSE_PARENTHESIS;
        }
        else if (strcmp(line, "OPEN_BRACKET") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_OPEN_BRACKET;
        }
        else if (strcmp(line, "CLOSE_BRACKET") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_CLOSE_BRACKET;
        }
        else if (strcmp(line, "OPEN_CURLY") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_OPEN_CURLY;
        }
        else if (strcmp(line, "CLOSE_CURLY") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_CLOSE_CURLY;
        }
        else if (strcmp(line, "INTEGER") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_INTEGER;
        }
        else if (strcmp(line, "FLOATINGPOINT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_FLOATINGPOINT;
        }
        else if (strcmp(line, "CHARACTER") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_CHARACTER;
        }
        else if (strcmp(line, "STRING") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_STRING;
        }
        else if (strcmp(line, "HEXADECIMAL") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_HEXADECIMAL;
        }
        else if (strcmp(line, "OCTAL") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_OCTAL;
        }
        else if (strcmp(line, "IDENTIFIER") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_IDENTIFIER;
        }
        else if (strcmp(line, "KEYWORD") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_KEYWORD;
        }
        else if (strcmp(line, "COMMA") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_COMMA;
        }
        else if (strcmp(line, "SEMICOLON") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_SEMICOLON;
        }
        else if (strcmp(line, "COLON") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_COLON;
        }
        else if (strcmp(line, "DOT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_DOT;
        }
        else if (strcmp(line, "ARROW") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_ARROW;
        }
        else if (strcmp(line, "QUESTION_MARK") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_QUESTION_MARK;
        }
        else if (strcmp(line, "WHITESPACE") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_WHITESPACE;
        }
        else if (strcmp(line, "LINE_COMMENT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_LINE_COMMENT;
        }
        else if (strcmp(line, "BLOCK_COMMENT") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_BLOCK_COMMENT;
        }
        else if (strcmp(line, "EOF") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_EOF;
        }
        else if (strcmp(line, "UNKNOWN") == 0)
        {
            tokensTypes[*tokenCount] = TOKEN_UNKNOWN;
        }
        else
        {
            fprintf(stderr, "Unknown token type: %s\n", line);
            free(tokensTypes);
            return NULL;
        }

        (*tokenCount)++;
    }

    fclose(file);
    return tokensTypes;
}

ASTType *readParserFile(const char *fileName, size_t *ASTTypeCount)
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

    ASTType *astTypes = malloc(100 * sizeof(ASTType));
    if (astTypes == NULL)
    {
        fprintf(stderr, "Memory allocation for astTypes failed!\n");
        fclose(file);
        return NULL;
    }
    *ASTTypeCount = 0;

    while (1)
    {
        char c = fgetc(file);
        if (c == EOF)
        {
            break;
        }
        else if (c == '#')
        {
            while ((c = fgetc(file)) != '#')
            {
                if (c == EOF || c == '\\')
                {
                    free(astTypes);
                    return NULL;
                }
            }
            continue;
        }
        else if (c == '\\')
        {
            continue;
        }
        else if (c == '\n')
        {
            continue;
        }
        else if (c == '\r')
        {
            continue;
        }
        else if (c == ' ')
        {
            continue;
        }

        size_t i = 0;
        char *line = malloc(40 * sizeof(char));
        line[i++] = c;
        while ((c = fgetc(file)) != '\\')
        {
            if (c == EOF)
            {
                free(astTypes);
                return NULL;
            }
            line[i++] = c;
        }
        line[i - 1] = '\0';

        if (*ASTTypeCount % 100 == 0)
        {
            astTypes = realloc(astTypes, (*ASTTypeCount + 100) * sizeof(My_TokenType));
            if (astTypes == NULL)
            {
                fprintf(stderr, "Memory reallocation for astTypes failed!\n");
                fclose(file);
                return NULL;
            }
        }

        if (strcmp(line, "PROGRAM") == 0)
        {
            astTypes[*ASTTypeCount] = AST_PROGRAM;
        }
        else if (strcmp(line, "GLOBAL_DECLARATION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_GLOBAL_DECLARATION;
        }
        else if (strcmp(line, "FUNCTION_DEFINITION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_FUNCTION_DEFINITION;
        }
        else if (strcmp(line, "DECLARATION_SPECIFIERS") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DECLARATION_SPECIFIERS;
        }
        else if (strcmp(line, "STORAGE_CLASS_SPECIFIER") == 0)
        {
            astTypes[*ASTTypeCount] = AST_STORAGE_CLASS_SPECIFIER;
        }
        else if (strcmp(line, "TYPE_SPECIFIER") == 0)
        {
            astTypes[*ASTTypeCount] = AST_TYPE_SPECIFIER;
        }
        else if (strcmp(line, "STRUCT_OR_UNION_SPECIFIER") == 0)
        {
            astTypes[*ASTTypeCount] = AST_STRUCT_OR_UNION_SPECIFIER;
        }
        else if (strcmp(line, "STRUCT_DECLARATION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_STRUCT_DECLARATION;
        }
        else if (strcmp(line, "SPECIFIER_QUALIFIER") == 0)
        {
            astTypes[*ASTTypeCount] = AST_SPECIFIER_QUALIFIER;
        }
        else if (strcmp(line, "TYPE_QUALIFIER") == 0)
        {
            astTypes[*ASTTypeCount] = AST_TYPE_QUALIFIER;
        }
        else if (strcmp(line, "STRUCT_DECLARATOR_LIST") == 0)
        {
            astTypes[*ASTTypeCount] = AST_STRUCT_DECLARATOR_LIST;
        }
        else if (strcmp(line, "STRUCT_DECLARATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_STRUCT_DECLARATOR;
        }
        else if (strcmp(line, "DECLARATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DECLARATOR;
        }
        else if (strcmp(line, "POINTER") == 0)
        {
            astTypes[*ASTTypeCount] = AST_POINTER;
        }
        else if (strcmp(line, "DIRECT_DECLARATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DIRECT_DECLARATOR;
        }
        else if (strcmp(line, "DIRECT_DECLARATOR_PRIME") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DIRECT_DECLARATOR_PRIME;
        }
        else if (strcmp(line, "ASSIGNMENT_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ASSIGNMENT_EXPRESSION;
        }
        else if (strcmp(line, "ASSIGNMENT_OPERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ASSIGNMENT_OPERATOR;
        }
        else if (strcmp(line, "CONDITIONAL_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_CONDITIONAL_EXPRESSION;
        }
        else if (strcmp(line, "LOGICAL_OR_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_LOGICAL_OR_EXPRESSION;
        }
        else if (strcmp(line, "LOGICAL_AND_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_LOGICAL_AND_EXPRESSION;
        }
        else if (strcmp(line, "BITWISE_OR_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_BITWISE_OR_EXPRESSION;
        }
        else if (strcmp(line, "BITWISE_XOR_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_BITWISE_XOR_EXPRESSION;
        }
        else if (strcmp(line, "BITWISE_AND_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_BITWISE_AND_EXPRESSION;
        }
        else if (strcmp(line, "EQUALITY_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_EQUALITY_EXPRESSION;
        }
        else if (strcmp(line, "EQUALITY_OPERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_EQUALITY_OPERATOR;
        }
        else if (strcmp(line, "RELATIONAL_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_RELATIONAL_EXPRESSION;
        }
        else if (strcmp(line, "RELATIONAL_OPERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_RELATIONAL_OPERATOR;
        }
        else if (strcmp(line, "SHIFT_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_SHIFT_EXPRESSION;
        }
        else if (strcmp(line, "SHIFT_OPERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_SHIFT_OPERATOR;
        }
        else if (strcmp(line, "ADDITIVE_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ADDITIVE_EXPRESSION;
        }
        else if (strcmp(line, "ADDITIVE_OPERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ADDITIVE_OPERATOR;
        }
        else if (strcmp(line, "MULTIPLICATIVE_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_MULTIPLICATIVE_EXPRESSION;
        }
        else if (strcmp(line, "MULTIPLICATIVE_OPERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_MULTIPLICATIVE_OPERATOR;
        }
        else if (strcmp(line, "CAST_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_CAST_EXPRESSION;
        }
        else if (strcmp(line, "UNARY_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_UNARY_EXPRESSION;
        }
        else if (strcmp(line, "UNARY_OPERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_UNARY_OPERATOR;
        }
        else if (strcmp(line, "PREFIX_UNARY_TOKEN") == 0)
        {
            astTypes[*ASTTypeCount] = AST_PREFIX_UNARY_TOKEN;
        }
        else if (strcmp(line, "POSTFIX_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_POSTFIX_EXPRESSION;
        }
        else if (strcmp(line, "POSTFIX_EXPRESSION_PRIME") == 0)
        {
            astTypes[*ASTTypeCount] = AST_POSTFIX_EXPRESSION_PRIME;
        }
        else if (strcmp(line, "POSTFIX_OPERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_POSTFIX_OPERATOR;
        }
        else if (strcmp(line, "PRIMARY_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_PRIMARY_EXPRESSION;
        }
        else if (strcmp(line, "LITERAL") == 0)
        {
            astTypes[*ASTTypeCount] = AST_LITERAL;
        }
        else if (strcmp(line, "TOKEN") == 0)
        {
            astTypes[*ASTTypeCount] = AST_TOKEN;
        }
        else if (strcmp(line, "EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_EXPRESSION;
        }
        else if (strcmp(line, "ARGUMENT_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ARGUMENT_EXPRESSION;
        }
        else if (strcmp(line, "TYPE_NAME") == 0)
        {
            astTypes[*ASTTypeCount] = AST_TYPE_NAME;
        }
        else if (strcmp(line, "ABSTRACT_DECLARATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ABSTRACT_DECLARATOR;
        }
        else if (strcmp(line, "DIRECT_ABSTRACT_DECLARATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DIRECT_ABSTRACT_DECLARATOR;
        }
        else if (strcmp(line, "DIRECT_ABSTRACT_DECLARATOR_PRIME") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DIRECT_ABSTRACT_DECLARATOR_PRIME;
        }
        else if (strcmp(line, "PARAMETER_LIST") == 0)
        {
            astTypes[*ASTTypeCount] = AST_PARAMETER_LIST;
        }
        else if (strcmp(line, "PARAMETER_DECLARATION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_PARAMETER_DECLARATION;
        }
        else if (strcmp(line, "INITIALIZER_LIST") == 0)
        {
            astTypes[*ASTTypeCount] = AST_INITIALIZER_LIST;
        }
        else if (strcmp(line, "DESIGNATION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DESIGNATION;
        }
        else if (strcmp(line, "DESIGNATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DESIGNATOR;
        }
        else if (strcmp(line, "CONSTANT_EXPRESSION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_CONSTANT_EXPRESSION;
        }
        else if (strcmp(line, "INITIALIZER") == 0)
        {
            astTypes[*ASTTypeCount] = AST_INITIALIZER;
        }
        else if (strcmp(line, "IDENTIFIER_LIST") == 0)
        {
            astTypes[*ASTTypeCount] = AST_IDENTIFIER_LIST;
        }
        else if (strcmp(line, "ENUM_SPECIFIER") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ENUM_SPECIFIER;
        }
        else if (strcmp(line, "ENUMERATOR_LIST") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ENUMERATOR_LIST;
        }
        else if (strcmp(line, "ENUMERATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ENUMERATOR;
        }
        else if (strcmp(line, "DECLARATION") == 0)
        {
            astTypes[*ASTTypeCount] = AST_DECLARATION;
        }
        else if (strcmp(line, "INIT_DECLARATOR_LIST") == 0)
        {
            astTypes[*ASTTypeCount] = AST_INIT_DECLARATOR_LIST;
        }
        else if (strcmp(line, "INIT_DECLARATOR") == 0)
        {
            astTypes[*ASTTypeCount] = AST_INIT_DECLARATOR;
        }
        else if (strcmp(line, "STATEMENT") == 0)
        {
            astTypes[*ASTTypeCount] = AST_STATEMENT;
        }
        else if (strcmp(line, "LABELED_STATEMENT") == 0)
        {
            astTypes[*ASTTypeCount] = AST_LABELED_STATEMENT;
        }
        else if (strcmp(line, "COMPOUND_STATEMENT") == 0)
        {
            astTypes[*ASTTypeCount] = AST_COMPOUND_STATEMENT;
        }
        else if (strcmp(line, "EXPRESSION_STATEMENT") == 0)
        {
            astTypes[*ASTTypeCount] = AST_EXPRESSION_STATEMENT;
        }
        else if (strcmp(line, "SELECTION_STATEMENT") == 0)
        {
            astTypes[*ASTTypeCount] = AST_SELECTION_STATEMENT;
        }
        else if (strcmp(line, "ITERATION_STATEMENT") == 0)
        {
            astTypes[*ASTTypeCount] = AST_ITERATION_STATEMENT;
        }
        else if (strcmp(line, "FOR_CONTROL") == 0)
        {
            astTypes[*ASTTypeCount] = AST_FOR_CONTROL;
        }
        else if (strcmp(line, "JUMP_STATEMENT") == 0)
        {
            astTypes[*ASTTypeCount] = AST_JUMP_STATEMENT;
        }
        else
        {
            fprintf(stderr, "Unknown ASTNode type: %s\n", line);
            free(astTypes);
            return NULL;
        }

        (*ASTTypeCount)++;
    }

    fclose(file);
    return astTypes;
}

char ** readFromFolder(const char *folderPath, size_t *fileCount)
{
    if (folderPath == NULL)
    {
        fprintf(stderr, "Folder path is NULL!\n");
        return NULL;
    }

    char **fileNames = malloc(100 * sizeof(char *));
    *fileCount = 0;

#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("test/inputs/*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Could not open directory\n");
        return NULL;
    }
    else
    {
        do
        {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) // If the entry is a regular file
            {
                if (*fileCount % 100 == 0)
                {
                    fileNames = realloc(fileNames, (*fileCount + 100) * sizeof(char *));
                    if (fileNames == NULL)
                    {
                        fprintf(stderr, "Memory reallocation for file names failed!\n");
                        FindClose(hFind);
                        return NULL;
                    }
                }
                fileNames[(*fileCount)++] = strdup(findFileData.cFileName);
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }
#else
    DIR *dir = opendir(folder_path);
    if (dir == NULL) 
    {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {
        const char *file_name = entry->d_name;

        if (strcmp(file_name, ".") != 0 && strcmp(file_name, "..") != 0) 
        {
            if (*fileCount % 100 == 0)
            {
                fileNames = realloc(fileNames, (*fileCount + 100) * sizeof(char *));
                if (fileNames == NULL)
                {
                    fprintf(stderr, "Memory reallocation for file names failed!\n");
                    closedir(dir);
                    return NULL;
                }
            }
            fileNames[(*fileCount)++] = file_name;
        }
    }

    closedir(dir);
#endif // _WIN32

    return fileNames;
}


