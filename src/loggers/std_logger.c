#include <stdarg.h>
#include <stdio.h>

#define MAX_FORMAT_LENGTH 250

static inline void log_message(const char* prefix, const char* format, va_list* args)
{
    #ifdef DISABLE_LOGGING
        va_end(*args);
        return;
    #endif

    char format_with_prefix[MAX_FORMAT_LENGTH];

    snprintf(format_with_prefix, MAX_FORMAT_LENGTH, "%s: %s\n", prefix, format);

    vprintf(format_with_prefix, *args);

    va_end(*args);
}

void log_critical(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    log_message("CRITICAL: ", format, &args);
}

void log_warning(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    log_message("WARNING: ", format, &args);
}

void log_info(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    log_message("INFO: ", format, &args);
}