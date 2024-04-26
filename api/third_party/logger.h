#ifndef GATEKEEPER_LOGGER_H_
#define GATEKEEPER_LOGGER_H_

///
/// @brief Represents the possible severity of a log.
///
typedef enum
{
    INFO,
    WARNING,
    CRITICAL
}
log_severity_t;

///
/// @brief Writes a log of info severity.
/// @param formath_args The format and arguements meant to shape a log.
///
#define write_info_log(format, args) write_custom_log(INFO, (format), (args))

///
/// @brief Writes a log of warning severity.
/// @param format_with_args The format and arguements meant to shape a log.
///
#define write_warning_log(format, args) write_custom_log(WARNING, (format), (args))

///
/// @brief Writes a log of critical severity.
/// @param format_with_args The format and arguements meant to shape a log.
///
#define write_critical_log(format, args) write_custom_log(CRITICAL, (format), (args))

///
/// @brief Writes a log based on specified format and arguments.
/// @param severity The severity level of a log.
/// @param format The format of a log. 
/// @param ... The parameters meant to supply the format of a log.
///
void write_custom_log(log_severity_t severity, const char* format, ...);

#endif  // GATEKEEPER_LOGGER_H_
