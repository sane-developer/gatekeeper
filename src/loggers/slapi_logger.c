#include <stdarg.h>
#include <stdio.h>

#define MAX_FORMAT_LENGTH 250

static inline void log_message(const int severity, const char *format, va_list* args)
{
    // TODO: Implement via dirsrv API.

    va_end(*args);
}

void log_critical(const char *format, ...)
{
    #ifdef DISABLE_LOGGING
        return;
    #endif

    va_list args;

    va_start(args, format);

    log_message(0, format, &args);
}

void log_warning(const char *format, ...)
{
    #ifdef DISABLE_LOGGING
        return;
    #endif

    va_list args;

    va_start(args, format);

    log_message(1, format, &args);
}

void log_info(const char *format, ...)
{
    #ifdef DISABLE_LOGGING
        return;
    #endif

    va_list args;

    va_start(args, format);

    log_message(2, format, &args);
}