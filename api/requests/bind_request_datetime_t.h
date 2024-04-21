#ifndef GATEKEEPER_BIND_REQUEST_DATETIME_T_H_
#define GATEKEEPER_BIND_REQUEST_DATETIME_T_H_

#include <stdint.h>
#include <time.h>

///
/// @brief Represents date and time information for a bind request.
///
typedef struct
{
    ///
    /// @brief Pointer to a string representing the full date [dd-MM-YYYY HH:mm].
    ///
    char* full_date;

    ///
    /// @brief Numeric representation of the day of the week [0 - Monday, 1 - Tuesday, ...].
    ///
    uint32_t day_of_week;

    ///
    /// @brief Numeric representation of the time of day [0-2359, respectively 00:00-23:59].
    ///
    uint32_t time_of_day;
}
bind_request_datetime_t;

///
/// @brief Sets the full date string based on the provided local time structure.
/// @param local_time Pointer to a variable representing the local time.
/// @param full_date Pointer to a string where the full date will be stored.
/// @return
///     - 1 when the full date is successfully set.
///     - 0 when an error occurs or the operation fails.
///
int set_full_date(const struct tm* local_time, char* full_date);

///
/// @brief Sets the day of the week based on the provided local time structure.
/// @param local_time Pointer to a variable representing the local time.
/// @param day_of_week Pointer to a variable where the day of the week will be stored.
/// @return
///     - 1 when the day of the week is successfully set.
///     - 0 when an error occurs or the operation fails.
///
int set_day_of_week(const struct tm* local_time, uint32_t* day_of_week);

///
/// @brief Sets the time of day based on the provided local time structure.
/// @param local_time Pointer to a variable representing the local time.
/// @param time_of_day Pointer to a variable where the time of day will be stored.
/// @return
///     - 1 when the time of day is successfully set.
///     - 0 when an error occurs or the operation fails.
///
int set_time_of_day(const struct tm* local_time, uint32_t* time_of_day);

#endif // GATEKEEPER_BIND_REQUEST_DATETIME_T_H_
