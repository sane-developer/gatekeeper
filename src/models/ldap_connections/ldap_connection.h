#ifndef LDAP_CONNECTION_H_
#define LDAP_CONNECTION_H_

#include <dirsrv/slapi-plugin.h>
#include <nspr4/prio.h>
#include <time.h>
#include "authentication_method.h"
#include "bind_request_status.h"

///
/// @brief Represents the LDAP connection that has been used to issue the bind request.
///
typedef struct
{
    ///
    /// @brief Pointer to an IP address that has been used to issue the bind request.
    ///
    PRNetAddr* ip;

    ///
    /// @brief Pointer to an IP address of the DNS that has been used to issue the bind request.
    ///
    PRNetAddr* dns;

    ///
    /// @brief Value representing the authentication method that has been used to issue the bind request.
    ///
    authentication_method_t auth;

    ///
    /// @brief Pointer to 
    ///
    struct tm* time;
}
ldap_connection_t;

///
/// @brief Fetches the LDAP connection parameters from directory server resources.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @param connection Pointer to an empty ldap_connection_t variable.
/// @return
///     - FETCHED_CONNECTION_PARAMETERS, when .
///     - Respective fetching error:
///         a) when ,
///         b) when ,
///         c) when ,
///         d) when .
///
bind_request_status_t fetch_ldap_connection_parameters(Slapi_PBlock* block, ldap_connection_t* connection);

///
/// @brief Disposes the resources allocated for LDAP connection parameters.
/// @param connection Pointer to a populated ldap_connection_t variable.
///
void dispose_ldap_connection_parameters(ldap_connection_t* connection);

#endif  // LDAP_CONNECTION_H_
