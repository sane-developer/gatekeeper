#ifndef BIND_REQUEST_STATE_H_
#define BIND_REQUEST_STATE_H_

///
/// @brief Represents the status of processed bind request.
///
typedef enum
{
    ///
    /// @brief Value indicating that request has been granted.
    ///
    REQUEST_GRANTED = 0,

    ///
    /// @brief Value indicating that request has been denied.
    ///
    REQUEST_DENIED = 1,

    ///
    /// @brief Value indicating that directory server did not return client DN.
    ///
    CLIENT_DN_FETCH_FAILURE = 2,

    ///
    /// @brief Value indicating that directory server did not return client roles.
    ///
    CLIENT_ROLES_FETCH_FAILURE = 3,

    ///
    /// @brief Value indicating that directory server did not return client groups.
    ///
    CLIENT_GROUPS_FETCH_FAILURE = 4,

    ///
    /// @brief Value indicating that directory server did not return client attributes.
    ///
    CLIENT_ATTRIBUTES_FETCH_FAILURE = 5,

    ///
    /// @brief Value indicating that directory server did not return client IPv4 address.
    ///
    CONNECTION_IP_FETCH_FAILURE = 6,

    ///
    /// @brief Value indicating that directory server did not return DNS IPv4 address.
    ///
    CONNECTION_DNS_FETCH_FAILURE = 7,

    ///
    /// @brief Value indicating that directory server did not return authentication method.
    ///
    CONNECTION_AUTH_FETCH_FAILURE = 8,

    ///
    /// @brief Value indicating that directory server did not return time of the connection.
    ///
    CONNECTION_TIME_FETCH_FAILURE = 9,

    ///
    /// @brief Value indicating that request parameters have been successfully fetched.
    ///
    FETCHED_PARAMETERS = 10,

    ///
    /// @brief Value indicating that request did not trigger any of the applied deny ACI rules.
    ///
    SATISFIED_DENY_ACI_RULES = 11,

    ///
    /// @brief Value indicating that request triggered all of the applied grant ACI rules.
    ///
    SATISFIED_GRANT_ACI_RULES = 12
}
bind_request_state_t;

#endif // BIND_REQUEST_STATE_H_
