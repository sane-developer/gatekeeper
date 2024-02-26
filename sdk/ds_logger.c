#include <stdarg.h>
#include "logger.h"

static inline void invoke_logger(const int severity, const char* format, va_list* args)
{
    (void) severity;
    (void) format;
    (void) args;

    // TODO: Implement via dirsrv API.
}

void log_critical(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    // TODO: Implement via dirsrv API: invoke_logger(SLAPI_CRITICAL, format, &args);

    va_end(args);
}

void log_warning(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    // TODO: Implement via dirsrv API: invoke_logger(SLAPI_WARNING, format, &args);

    va_end(args);
}

void log_info(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    // TODO: Implement via dirsrv API: invoke_logger(SLAPI_INFO, format, &args);

    va_end(args);
}