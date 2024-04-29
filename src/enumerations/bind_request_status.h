#ifndef BIND_REQUEST_STATUS_H_
#define BIND_REQUEST_STATUS_H_

///
/// @brief Represents the statuses of bind request on each evaluation step.
///
typedef enum
{
    ///
    /// @brief Value indicating that a bind request has been granted.
    ///
    REQUEST_GRANTED = 0,
    
    ///
    /// @brief Value indicating that a bind request has been denied.
    ///
    REQUEST_DENIED = 1,
    
    ///
    /// @brief Value indicating that an error has occured while fetching the DN of the LDAP client.
    ///
    FAILED_TO_GET_CLIENT_DN = 2,
    
    ///
    /// @brief Value indicating that an error has occured while fetching the roles of the LDAP client.
    ///
    FAILED_TO_GET_CLIENT_ROLES = 3,
    
    ///
    /// @brief Value indicating that an error has occured while fetching the groups of the LDAP client.
    ///
    FAILED_TO_GET_CLIENT_GROUPS = 4,
    
    ///
    /// @brief Value indicating that an error has occured while fetching the attributes of the LDAP client.
    ///
    FAILED_TO_GET_CLIENT_ATTRIBUTES = 5,
    
    ///
    /// @brief Value indicating that an error has occured while fetching the IP address used to issue the bind request.
    ///
    FAILED_TO_GET_CONNECTION_IP = 6,
    
    ///
    /// @brief Value indicating that an error has occured while fetching the IP address of the DNS used to issue the bind request.
    ///
    FAILED_TO_GET_CONNECTION_DNS = 7,
    
    ///
    /// @brief Value indicating that an error has occured while fetching the time of the connection used to issue the bind request.
    ///
    FAILED_TO_GET_CONNECTION_TIME = 8,
    
    ///
    /// @brief Value indicating that an error has occured while fetching the authentication method used to issue the bind request.
    ///
    FAILED_TO_GET_CONNECTION_AUTH = 9,
    
    ///
    /// @brief Value indicating that all of the LDAP client parameters have been successfully fetched.
    ///
    FETCHED_CLIENT_PARAMETERS = 10,
    
    ///
    /// @brief Value indicating that all of the LDAP connection parameters have been successfully fetched.
    ///
    FETCHED_CONNECTION_PARAMETERS = 11,
    
    ///
    /// @brief Value indicating that a bind request has satisfied the ACI rules of grant type.
    ///
    SATISFIED_GRANT_ACI_RULES = 12,
    
    ///
    /// @brief Value indicating that a bind request has satisfied the ACI rules of deny type.
    ///
    SATISFIED_DENY_ACI_RULES = 13
}
bind_request_status_t;

#endif  // BIND_REQUEST_STATUS_H_
