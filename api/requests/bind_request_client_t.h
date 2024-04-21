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
/// @brief Sets the DN (Distinguished Name) for the client based on the operation parameters block.
/// @param block Pointer to the operation parameters block.
/// @param dn Pointer to a string representing the DN for the client.
/// @return
///     - 1 when the DN is successfully set for the client.
///     - 0 when an error occurs or the operation fails.
///
int set_client_dn(Slapi_PBlock* block, char* dn);

///
/// @brief Sets the IPv4 address for the client based on the operation parameters block.
/// @param block Pointer to the operation parameters block.
/// @param ip Pointer to a variable representing the IPv4 address for the client.
/// @return
///     - 1 when the IPv4 address is successfully set for the client.
///     - 0 when an error occurs or the operation fails.
///
int set_client_ip(Slapi_PBlock* block, uint32_t* ip);

///
/// @brief Sets the IPv4 DNS address for the client based on the operation parameters block.
/// @param block Pointer to the operation parameters block.
/// @param dns Pointer to a variable representing the IPv4 DNS address for the client.
/// @return
///     - 1 when the DNS address is successfully set for the client.
///     - 0 when an error occurs or the operation fails.
///
int set_client_dns(Slapi_PBlock* block, uint32_t* dns);

///
/// @brief Sets the authentication method for the client based on the operation parameters block.
/// @param block Pointer to the operation parameters block.
/// @param auth Pointer to a variable representing the authentication method for the client.
/// @return
///     - 1 when the authentication method is successfully set for the client.
///     - 0 when an error occurs or the operation fails.
///
int set_client_auth(Slapi_PBlock* block, authentication_method_t* auth);

#endif  // GATEKEEPER_BIND_REQUEST_CLIENT_T_H_
