/** 
 * @file logger.h
 * @brief Header file for the logger utility.
 * 
 * This file defines the logger functions for initializing, closing, and logging debug messages.
 * It includes a macro for debug printing that includes timestamps and file/line information.
 * This logger is designed to be thread-safe and can be used across different platforms.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

/**
 * @typedef PrintFunction
 * @brief Function pointer type for printing data.
 *
 * This function pointer is used to define how the data in different structures
 * should be printed. It takes a pointer to the data and returns nothing.
 */
typedef void (*PrintFunction)(const void *data);

/**
 * @brief Initializes the logging system.
 *
 * Opens the log file ("compiler.log") for writing and initializes
 * internal synchronization primitives for thread-safe logging.
 * If the log file cannot be opened, falls back to stderr.
 * This function is safe to call multiple times; initialization
 * happens only once.
 */
void logger_init(void);

/**
 * @brief Closes the logging system.
 *
 * Flushes and closes the log file if it was successfully opened.
 * After calling this function, no further logging should be done
 * unless logger_init() is called again.
 */
void logger_close(void);

/**
 * @brief Logs a formatted debug message to the log file.
 *
 * This function writes the formatted message (like printf) to the log 
 * file and stderr, in a thread-safe manner. It requires the logging system
 * to be initialized first by calling logger_init().
 *
 * @param fmt The format string (printf-style).
 * @param ... Arguments corresponding to the format string.
 */
void logger_debug(const char *fmt, ...);

#ifdef DEBUG
#include <time.h>
/**
 * @def DEBUG_PRINT(...)
 * @brief Logs a debug message to both stderr and the log file with timestamp and source location.
 *
 * This macro expands to nothing unless compiled with DEBUG defined.
 * When enabled, it prints the formatted debug message to stderr and to the log file,
 * including a timestamp, source file name, and line number.
 *
 * Usage example:
 * @code
 * DEBUG_PRINT("Value of x: %d\n", x);
 * @endcode
 */
#define DEBUG_PRINT(...) do {                                               \
    time_t t = time(NULL);                                                  \
    struct tm *tm_info = localtime(&t);                                     \
    char timestamp[26];                                                     \
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);   \
                                                                            \
    fprintf(stderr, "[DEBUG %s] %s:%d: ", timestamp, __FILE__, __LINE__);   \
    fprintf(stderr, __VA_ARGS__);                                           \
                                                                            \
    logger_debug("[%s] %s:%d: ", timestamp, __FILE__, __LINE__);            \
    logger_debug(__VA_ARGS__);                                              \
} while (0)
#else
/**
 * @def DEBUG_PRINT(...)
 * @brief Logs a debug message to both stderr and the log file with timestamp and source location.
 *
 * This macro expands to nothing unless compiled with DEBUG defined.
 * When enabled, it prints the formatted debug message to stderr and to the log file,
 * including a timestamp, source file name, and line number.
 *
 * Usage example:
 * @code
 * DEBUG_PRINT("Value of x: %d\n", x);
 * @endcode
 */
#define DEBUG_PRINT(...) ((void)0)
#endif

#endif // LOGGER_H