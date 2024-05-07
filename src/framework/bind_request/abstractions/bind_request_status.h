#ifndef BIND_REQUEST_STATUS_H
#define BIND_REQUEST_STATUS_H

///
/// @brief
///
typedef enum
{
    ///
    /// @brief
    ///
    REQUEST_GRANTED = 0,

    ///
    /// @brief
    ///
    REQUEST_DENIED = 1,

    ///
    /// @brief
    ///
    REQUEST_DN_FETCH_FAILURE,

    ///
    /// @brief
    ///
    REQUEST_IP_FETCH_FAILURE,

    ///
    /// @brief
    ///
    REQUEST_DNS_FETCH_FAILURE,

    ///
    /// @brief
    ///
    REQUEST_ROLES_FETCH_FAILURE,

    ///
    /// @brief
    ///
    REQUEST_GROUPS_FETCH_FAILURE,

    ///
    /// @brief
    ///
    REQUEST_ATTRIBUTES_FETCH_FAILURE,
    ///

    /// @brief
    ///
    REQUEST_PARAMETERS_FETCH_SUCCESS,

    ///
    /// @brief
    ///
    REQUEST_SATISFIED_GRANT_RULES,

    ///
    /// @brief
    ///
    REQUEST_SATISFIED_DENY_RULES
}
bind_request_status_t, bind_request_error_t;

#endif  // BIND_REQUEST_STATUS_H
