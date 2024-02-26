#include <dirsrv/slapi-plugin.h>
#include <stdarg.h>
#include <stdio.h>
#include "logger.h"

static inline void invoke_logger(const int severity, const char* format, va_list* args)
{
    char buffer[1024];

    vsnprintf(buffer, sizeof(buffer), format, *args);

    slapi_log_error(severity, "gatekeeper", "%s\n", buffer);
}

void log_critical(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    invoke_logger(SLAPI_LOG_CRIT, format, &args);
    
    va_end(args);
}

void log_warning(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    invoke_logger(SLAPI_LOG_WARNING, format, &args);

    va_end(args);
}

void log_info(const char* format, ...)
{
    va_list args;

    va_start(args, format);

    invoke_logger(SLAPI_LOG_INFO, format, &args);

    va_end(args);
}
