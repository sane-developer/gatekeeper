#ifndef BIND_REQUEST_CONNECTION_H_
#define BIND_REQUEST_CONNECTION_H_

#include "bind_request_state.h"
#include <dirsrv/slapi-plugin.h>
#include <nspr4/prio.h>
#include <time.h>

///
/// @brief Represents the numerical representation of supported authentication methods of LDAPv3 protocol.
///
typedef enum
{
    ///
    /// @brief Value indicating that SSL method has been used by the LDAP client.
    ///
    SSL,

    ///
    /// @brief value indicating that SIMPLE method has been used by the ldap client.
    ///
    SIMPLE,

    ///
    /// @brief Value indicating that anonymous method has been used by the LDAP client.
    ///
    ANONYMOUS,

    ///
    /// @brief Value indicating that SASL GSSAPI method has been used by the LDAP client.
    ///
    SASL_GSSAPI,

    ///
    /// @brief Value indicating that SASL EXTERNAL method has been used by the LDAP client.
    ///
    SASL_EXTERNAL,

    ///
    /// @brief Value indicating that SASL DIGEST-MD5 method has been used by the LDAP client.
    ///
    SASL_DIGEST_MD5
}
authentication_t;

///
/// @brief Represents the connection used by LDAP client to issue the bind request.
///
typedef struct
{
    ///
    /// @brief Pointer to a PRNetAddr variable that holds IPv4 address that was used by the LDAP client.
    ///
    PRNetAddr* ip;

    ///
    /// @brief Pointer to a PRNetAddr variable that holds IPv4 address of DNS that was used by the LDAP client.
    ///
    PRNetAddr* dns; 

    ///
    /// @brief Numerical representation of authentication method that was used by the LDAP client.
    ///
    authentication_t auth;

    ///
    /// @brief Date & time metadata of the connection that was issued by the LDAP client.
    ///
    struct tm* time;
}
bind_request_connection_t;

///
/// @brief Fetches the bind request connection parameters from directory server and system resources.
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param request Pointer to bind_request_connection_t variable that stores the bind request connection parameters.
/// @return
///     - FETCHED_PARAMETERS, when all of the bind request connection parameters were successfully fetched.
///     - CONNECTION_IP_FETCH_FAILURE, when directory server did not return IPv4 address used to connect.
///     - CONNECTION_DNS_FETCH_FAILURE, when directory server did not return DNS IPv4 address used to connect.
///     - CONNECTION_AUTH_FETCH_FAILURE, when directory server did not return authentcation method used to connect.
///     - CONNECTION_TIME_FETCH_FAILURE, when system clock did not return valid value.
///
bind_request_state_t fetch_bind_request_connection_parameters(Slapi_PBlock* block, bind_request_connection_t* connection);

///
/// @brief Disposes the parameters allocated for the bind request connection parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request connection parameters.
///
void dispose_bind_request_connection_parameters(bind_request_connection_t* connection);

#endif  // BIND_REQUEST_CONNECTION_H_
