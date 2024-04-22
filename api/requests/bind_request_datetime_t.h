#ifndef GATEKEEPER_BIND_REQUEST_DATETIME_T_H_
#define GATEKEEPER_BIND_REQUEST_DATETIME_T_H_

#include <stdint.h>

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
/// @brief Initializes the LDAP client connection date and time metadata.
/// @param request Pointer to a zeroed bind_request_datetime_t variable.
///
void initialize_bind_request_datetime(bind_request_datetime_t* const datetime);

#endif // GATEKEEPER_BIND_REQUEST_DATETIME_T_H_
