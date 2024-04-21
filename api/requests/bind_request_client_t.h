#ifndef GATEKEEPER_BIND_REQUEST_CLIENT_T_H_
#define GATEKEEPER_BIND_REQUEST_CLIENT_T_H_

#include <dirsrv/slapi-plugin.h>
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
/// @brief Represents the string representations of the supported authentication method types.
///
const char stringified_auth_methods[6][16] =
{
    [SSL] = "ssl",
    [NONE] = "none",
    [SIMPLE] = "simple",
    [SASL_GSSAPI] = "sasl gssapi",
    [SASL_EXTERNAL] = "sasl external",
    [SASL_DIGEST_MD5] = "sasl digest-md5"
};

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
    
    ///
    /// @brief The groups that are assigned to the client.
    ///
    char* groups;

    ///
    /// @brief The attributes that are assigned to the client.
    ///
    char* attributes;
}
bind_request_client_t;

///
/// @brief Sets the client DN that was retrieved from the directory server.
///
/// @param block Pointer to operation parameters supplied by directory server.
/// @param dst Pointer to the char variable that stores the DN. 
///
/// @return An integer representing status of the performed operation:
///     - 1 if the DN has been successfully retrieved and set,
///     - 0 if an error occured.
///
int set_client_dn(Slapi_PBlock* block, char* dst);

///
/// @brief Sets the client IPv4 address that was retrieved from the directory server.
///
/// @param block Pointer to operation parameters supplied by directory server.
/// @param dst Pointer to the uint32_t variable that stores the IPv4 address. 
///
/// @return An integer representing status of the performed operation:
///     - 1 if the IPv4 address has been successfully retrieved and set,
///     - 0 if an error occured.
///
int set_client_ip(Slapi_PBlock* block, uint32_t* dst);

///
/// @brief Sets the client DNS IPv4 address that was retrieved from the directory server.
///
/// @param block Pointer to operation parameters supplied by directory server.
/// @param dst Pointer to the uint32_t variable that stores the IPv4 address. 
///
/// @return An integer representing status of the performed operation:
///     - 1 if the IPv4 address have been successfully retrieved and set,
///     - 0 if an error occured.
///
int set_client_dns(Slapi_PBlock* block, uint32_t* dst);

///
/// @brief Sets the client authentication method type that was retrieved from the directory server.
///
/// @param block Pointer to operation parameters supplied by directory server.
/// @param dst Pointer to the authentication_method_t variable that stores the method type. 
///
/// @return An integer representing status of the performed operation:
///     - 1 if the authentication method have been successfully retrieved and set,
///     - 0 if an error occured.
///
int set_client_auth(Slapi_PBlock* block, authentication_method_t* dst);

///
/// @brief Sets the client groups that were retrieved from the directory server.
///
/// @param block Pointer to operation parameters supplied by directory server.
/// @param dst Pointer to the char* variable that stores the groups divided by ';'. 
///
/// @return An integer representing status of the performed operation:
///     - 1 if the groups have been successfully retrieved and set,
///     - 0 if an error occured.
///
int set_client_groups(Slapi_PBlock* block, char* dst);

///
/// @brief Sets the client attributes that were retrieved from the directory server.
///
/// @param block Pointer to operation parameters supplied by directory server.
/// @param dst Pointer to the char variable that stores the attributes divided by ';'. 
///
/// @return An integer representing status of the performed operation:
///     - 1 if the attributes have been successfully retrieved and set,
///     - 0 if an error occured.
///
int set_client_attributes(Slapi_PBlock* block, char* dst);

#endif  // GATEKEEPER_BIND_REQUEST_CLIENT_T_H_
