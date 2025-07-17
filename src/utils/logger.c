#include "utils/logger.h"

#ifdef _WIN32
typedef CRITICAL_SECTION LogMutex;
#define LOGGER_MUTEX_INIT(mutex) InitializeCriticalSection(&mutex)
#define LOGGER_MUTEX_LOCK(mutex) EnterCriticalSection(&mutex)
#define LOGGER_MUTEX_UNLOCK(mutex) LeaveCriticalSection(&mutex)
#else
typedef pthread_mutex_t LogMutex;
#define LOGGER_MUTEX_INIT(mutex) pthread_mutex_init(&mutex, NULL)
#define LOGGER_MUTEX_LOCK(mutex) pthread_mutex_lock(&mutex)
#define LOGGER_MUTEX_UNLOCK(mutex) pthread_mutex_unlock(&mutex)
#endif

static FILE *log_file = NULL;
static LogMutex log_mutex;
static int log_initialized = 0;

void logger_init(void)
{
    if (log_initialized) 
    {
        return;
    }

    log_file = fopen("compiler.log", "w");
    if (!log_file) 
    {
        log_file = stderr;
    }

    LOGGER_MUTEX_INIT(log_mutex);
    log_initialized = 1;
}

void logger_close(void)
{
    if (log_file && log_file != stderr)
    {
        fclose(log_file);
    }
}

void logger_debug(const char *fmt, ...)
{
    if (!log_initialized) 
    {
        logger_init();
    }

    LOGGER_MUTEX_LOCK(log_mutex);

    va_list args;
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);

    fflush(log_file);
    LOGGER_MUTEX_UNLOCK(log_mutex);
}
