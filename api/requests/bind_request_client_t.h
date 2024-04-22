#ifndef GATEKEEPER_BIND_REQUEST_CLIENT_T_H_
#define GATEKEEPER_BIND_REQUEST_CLIENT_T_H_

#include <slapi-plugin.h>
#include <stdint.h>

///
/// @brief Represents the authentication methods supported by the directory server.
///
typedef enum
{
    SSL,
    NONE,
    SIMPLE,
    SASL_GSSAPI,
    SASL_EXTERNAL,
    SASL_DIGEST_MD5
}
authentication_method_t;

///
/// @brief Represents the metadata about the client retrived from the directory server.
///
typedef struct
{
    ///
    /// @brief The DN that represents the client.
    ///
    char* dn;

    ///
    /// @brief The IPv4 address that was used by the client.
    ///
    uint32_t ip;

    ///
    /// @brief The IPv4 DNS address that was used by the client.
    ///
    uint32_t dns;

    ///
    /// @brief The authentication method that was used by the client.
    ///
    authentication_method_t auth;
}
bind_request_client_t;

///
/// @brief Attempts to initialize LDAP client metadata.
/// @param block Pointer to a key-value pair storage for bind operation parameters.
/// @param client Pointer to a zeroed bind_request_client_t variable.
/// @return
///     - 1, when all of the fields were successfully initialized.
///     - 0, when any of the fields could not be initialized.
///
int initialize_bind_request_client(const Slapi_PBlock* const block, bind_request_client_t* const client);

///
/// @brief Disposes metadata inside bind_request_client_t variable.
/// @param client Pointer to a populated bind_request_client_t variable.
///
void dispose_bind_request_client(bind_request_client_t* client);

#endif  // GATEKEEPER_BIND_REQUEST_CLIENT_T_H_
