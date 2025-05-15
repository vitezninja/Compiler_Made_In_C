#include <stdio.h>
#include <stdlib.h>
#include "../src/utils/file_reader.h"
#include "../src/utils/error.h"
#include "../src/utils/my_string.h"
#include "../src/utils/token.h"
#include "../src/utils/AST.h"
#include "../src/VM/vm.h"

static int testLexer(const char * inputFileName, const char *resultFileName);

static int testParser(const char * inputFileName, const char *resultFileName);

int main()
{
    int testCount = 0;
    int passed = 0;

    const char *input_folder_path = "test/inputs";
    const char *result_folder_path = "test/results";

    size_t fileCount = 0;
    printf("Checking for test files...\n");
    char **inputFileNames = readFromFolder(input_folder_path, &fileCount);

    for (size_t i = 0; i < fileCount; i++)
    {
        char *inputFilePath = malloc(strlen(inputFileNames[i]) + strlen(input_folder_path) + 2);
        strcpy(inputFilePath, "");
        strcat(inputFilePath, input_folder_path);
        strcat(inputFilePath, "/");
        strcat(inputFilePath, inputFileNames[i]);

        char *resultFilePath = malloc(strlen(inputFileNames[i]) + strlen(result_folder_path) + 2);
        strcpy(resultFilePath, "");
        strcat(resultFilePath, result_folder_path);
        strcat(resultFilePath, "/");
        char* resultFileName = stripFrom(inputFileNames[i], '.', 1);
        strcat(resultFilePath, resultFileName);

        printf("Testing: %s - %s\n", inputFileNames[i], resultFileName);

        char* testType = stripFrom(resultFileName, '_', 0);

        int result = 0;
        if (strcmp(testType, "lexer") == 0)
        {
            result = testLexer(inputFilePath, resultFilePath);    
            
        }
        else if (strcmp(testType, "parser") == 0)
        {
            result = testParser(inputFilePath, resultFilePath);
        }
        else
        {
            printf("\tInvalid test type: %s\n", testType);
            free(inputFilePath);
            free(resultFilePath);
            free(resultFileName);
            free(testType);
            continue;
        }

        free(inputFilePath);
        free(resultFilePath);
        free(testType);
        
        testCount++;
        if (result == -1)
        {
            printf("\tError testing %s\n", resultFileName);
            continue;
        }
        else if (result == 0)
        {
            printf("\tTest passed!\n");
            passed++;
        }
        else
        {
            printf("\tTest failed!\n");
        }

        free(resultFileName);
    }

    for (size_t i = 0; i < fileCount; i++)
    {
        free(inputFileNames[i]);
    }
    free(inputFileNames);

    printf("Tests passed: %d/%d\n", passed, testCount);
    if (passed == testCount)
    {
        printf("\tAll tests passed!\n");
        return 0;
    }

    printf("\tSome tests failed!\n");
    return -1;
}

static int testLexer(const char * inputFileName, const char *resultFileName)
{
    if (inputFileName == NULL)
    {
        printf("Invalid input file name.\n");
        return -1;
    }

    if (resultFileName == NULL)
    {
        printf("Invalid result file name.\n");
        return -1;
    }

    char *fileContent = readFromFile(inputFileName);
    if (fileContent == NULL)
    {
        return -1;
    }

    //Lex the input
    size_t inputTokenCount = 0;
    Token **inputTokens = lexFile(fileContent, &inputTokenCount);
    if (inputTokens == NULL)
    {
        printf("\tError lexing input file.\n");
        freeFileContent(fileContent);
        return -1;
    }
    freeFileContent(fileContent);

    //Count whitespaces and comment tokens
    size_t removedTokens = 0;
    for (size_t i = 0; i < inputTokenCount; i++)
    {
        if (inputTokens[i]->type == TOKEN_WHITESPACE || inputTokens[i]->type == TOKEN_BLOCK_COMMENT || inputTokens[i]->type == TOKEN_LINE_COMMENT)
        {
            removedTokens++;
        }
    }
    
    //Read the result file
    size_t resultTokenCount = 0;
    My_TokenType *resultTokens = readLexerFile(resultFileName, &resultTokenCount);
    if (resultTokens == NULL)
    {
        deleteTokens(inputTokens, inputTokenCount);
        return -1;
    }

    //Compare the tokens
    printf("\tInput tokens:\n");
    for (size_t i = 0; i < inputTokenCount; i++)
    {
        printToken(inputTokens[i]);
    }

    printf("\tResult tokens:\n");
    for (size_t i = 0; i < resultTokenCount; i++)
    {
        printf("\t%s\n", getType(resultTokens[i]));
    }
        
    if (inputTokenCount - removedTokens != resultTokenCount)
    {
        printf("\tToken count mismatch: \n\t actual: %d \t  expected: %d\n", inputTokenCount - removedTokens, resultTokenCount);
        deleteTokens(inputTokens, inputTokenCount);
        free(resultTokens);
        return 1;
    }

    size_t resultTokenIndex = 0;
    for (size_t inputTokenIndex = 0; inputTokenIndex < resultTokenCount; inputTokenIndex++)
    {
        if (inputTokens[inputTokenIndex]->type == TOKEN_WHITESPACE || inputTokens[inputTokenIndex]->type == TOKEN_BLOCK_COMMENT || inputTokens[inputTokenIndex]->type == TOKEN_LINE_COMMENT)
        {
            continue;
        }

        if (inputTokens[inputTokenIndex]->type != resultTokens[resultTokenIndex])
        {
            printf("\tToken mismatch at index %d: %s != %s\n", resultTokenIndex, getType(inputTokens[inputTokenIndex]->type), getType(resultTokens[resultTokenIndex]));
            deleteTokens(inputTokens, inputTokenCount);
            free(resultTokens);
            return 1;
        }
        resultTokenIndex++;
    }

    //Delete input tokens
    deleteTokens(inputTokens, inputTokenCount);
    //Delete result tokens
    free(resultTokens);
    return 0;
}

static int testParser(const char * inputFileName, const char *resultFileName)
{
    if (inputFileName == NULL)
    {
        printf("Invalid input file name.\n");
        return -1;
    }

    if (resultFileName == NULL)
    {
        printf("Invalid result file name.\n");
        return -1;
    }

    char *fileContent = readFromFile(inputFileName);
    if (fileContent == NULL)
    {
        return -1;
    }

    //Lex the input
    size_t tokenCount = 0;
    Token **tokens = lexFile(fileContent, &tokenCount);
    if (tokens == NULL)
    {
        printf("Error lexing input file.\n");
        freeFileContent(fileContent);
        return -1;
    }

    freeFileContent(fileContent);

    //Parse the tokens
    ASTNode *root = parseTokens(tokens, tokenCount);
    if (root == NULL)
    {
        printf("Error parsing tokens.\n");
        deleteTokens(tokens, tokenCount);
        return -1;
    }

    //Flaten the AST into an array
    size_t inputASTTypeCount = 0;
    ASTNode *inputAST = flattenAST(root, &inputASTTypeCount);

    //Read the result file
    size_t resultASTTypeCount = 0;
    ASTType *resultASTTypes = readParserFile(resultFileName, &resultASTTypeCount);
    if (resultASTTypes == NULL)
    {
        return -1;
    }

    //Compare the AST types
    if (inputASTTypeCount != resultASTTypeCount)
    {
        printf("\tAST type count mismatch: \n\t actual: %d \t  expected: %d\n", inputASTTypeCount, resultASTTypeCount);
        return 1;
    }
    for (size_t i = 0; i < resultASTTypeCount; i++)
    {
        if (inputAST[i].type != resultASTTypes[i])
        {
            printf("\tAST type mismatch at index %d: %s != %s\n", i, getASTType(inputAST[i].type), getASTType(resultASTTypes[i]));
            return 1;
        }
    }

    //Delete input AST
    deleteASTNode(inputAST);
    //Delete result AST types
    free(resultASTTypes);
    //Delete tokens
    deleteTokens(tokens, tokenCount);
    return 0;
}