#ifndef GATEKEEPER_LOGGER_H
#define GATEKEEPER_LOGGER_H

///
/// @brief Writes a log with info severity.
/// @param format The format of the log message.
/// @param ... The arguments supplying the format of the log message.
///
void log_critical(const char* format, ...);

///
/// @brief Writes a log with info severity.
/// @param format The format of the log message.
/// @param ... The arguments supplying the format of the log message.
///
void log_warning(const char* format, ...);

///
/// @brief Writes a log with info severity.
/// @param format The format of the log message.
/// @param ... The arguments supplying the format of the log message.
///
void log_info(const char* format, ...);

#endif // GATEKEEPER_LOGGER_H