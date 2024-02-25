#include <stdarg.h>
#include <stdio.h>
#include "logger.h"

static inline void invoke_logger(const char* prefix, const char* format, va_list* args)
{
    printf("%s", prefix);

    vprintf(format, *args);

    printf("\n");
}

void log_critical(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    invoke_logger("CRITICAL: ", format, &args);

    va_end(args);
}

void log_warning(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    invoke_logger("WARNING: ", format, &args);

    va_end(args);
}

void log_info(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    invoke_logger("INFO: ", format, &args);

    va_end(args);
}