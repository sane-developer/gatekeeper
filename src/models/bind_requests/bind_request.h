#ifndef BIND_REQUEST_H_
#define BIND_REQUEST_H_

#include "ldap_client.h"
#include "ldap_connection.h"

///
/// @brief Represents a bind request.
///
typedef struct
{
    ///
    /// @brief Parameters of the LDAP client that issued the bind request.
    ///
    ldap_client_t client;
    
    ///
    /// @brief Parameters of the LDAP connection that was used to issue the bind request.
    ///
    ldap_connection_t connection;
    
    ///
    /// @brief Pointer to a string represeting the label of the ACI rule that caused the bind request to be denied.
    ///
    char* note;
}
bind_request_t;

#endif  // BIND_REQUEST_H_
