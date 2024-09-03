#ifndef FILE_READING_H
#define FILE_READING_H

#include <stdio.h>
#include <stdlib.h>

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
 *       using `freeFileContent`. If a file cannot be read, the corresponding 
 *       entry in the returned array may be `NULL`.
 */
char **readFromFiles(char **fileNames, const size_t fileCount);

/**
 * Frees the memory allocated for the contents of multiple files.
 *
 * The `freeFileContent` function deallocates the memory used to store the contents 
 * of multiple files, as well as the memory used for the array holding those contents.
 *
 * @param FileContents An array of `char*` where each element points to the contents 
 *                     of a file. The array should contain `fileCount` elements.
 * @param fileCount The number of files, i.e., the number of elements in the 
 *                  `FileContents` array.
 *
 * @note If `FileContents` is `NULL`, the function does nothing and logs an error 
 *       message to `stderr`. The caller should ensure `FileContents` is properly 
 *       allocated before passing it to this function.
 */
void freeFileContent(char **FileContents, const size_t fileCount);

#endif