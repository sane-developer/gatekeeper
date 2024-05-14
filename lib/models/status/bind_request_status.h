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
    FAILED_TO_FETCH_CLIENT_DN,

    ///
    /// @brief
    ///
    FAILED_TO_FETCH_CLIENT_IP,

    ///
    /// @brief
    ///
    FAILED_TO_FETCH_CLIENT_DNS,

    ///
    /// @brief
    ///
    FAILED_TO_FETCH_CLIENT_ROLES,

    ///
    /// @brief
    ///
    FAILED_TO_FETCH_CLIENT_GROUPS,

    ///
    /// @brief
    ///
    FAILED_TO_FETCH_CLIENT_ATTRIBUTES,

    ///
    /// @brief
    ///
    FAILED_TO_SATISFY_DENY_RULES,

    ///
    /// @brief
    ///
    FAILED_TO_SATISFY_GRANT_RULES
}
bind_request_status_t, bind_request_error_t;

#endif  // BIND_REQUEST_STATUS_H
