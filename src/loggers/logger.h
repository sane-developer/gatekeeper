#ifndef GATEKEEPER_LOGGER_H
#define GATEKEEPER_LOGGER_H

///
/// @brief Write log with critical severity.
/// @param format The format of the log.
/// @param ... The arguments respective to the format.
///
void log_critical(const char *format, ...);

///
/// @brief Write log with warning severity.
/// @param format The format of the log.
/// @param ... The arguments respective to the format.
///
void log_warning(const char *format, ...);

///
/// @brief Write log with info severity.
/// @param format The format of the log.
/// @param ... The arguments respective to the format.
///
void log_info(const char *format, ...);

#endif