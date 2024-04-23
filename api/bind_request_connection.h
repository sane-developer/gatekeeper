#ifndef BIND_REQUEST_CONNECTION_H_
#define BIND_REQUEST_CONNECTION_H_

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

#endif  // BIND_REQUEST_CONNECTION_H_
