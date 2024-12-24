#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif // _WIN32

#include "../src/utils/token.h"
#include "../src/utils/AST.h"
#include "../src/utils/error.h"

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
int getFileSize(FILE *file);

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
char *readFromFile(const char *fileName);

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
char **readFromFiles(const char **fileNames, const size_t fileCount);

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
void freeFileContent(char *fileContent);

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
void freeFileContents(char **fileContents, const size_t fileCount);

My_TokenType *readLexerFile(const char *fileName, size_t *tokenCount);

ASTType *readParserFile(const char *fileName, size_t *ASTTypeCount);

char **readFromFolder(const char *folderPath, size_t *fileCount);

#endif // FILE_READER_H