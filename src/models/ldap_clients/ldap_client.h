#ifndef LDAP_CLIENT_H_
#define LDAP_CLIENT_H_

#include <dirsrv/slapi-plugin.h>
#include "bind_request_status.h"

///
/// @brief Represents the LDAP client that issued a bind request.
///
typedef struct
{
    ///
    /// @brief Pointer to a string representing the DN of the LDAP client.
    ///
    char* dn;

    ///
    /// @brief Pointer to a string representing the roles of the LDAP client (divided via ';').
    ///
    char* roles;
    
    ///
    /// @brief Pointer to a string representing the groups of the LDAP client (divided via ';').
    ///
    char* groups;
    
    ///
    /// @brief Pointer to a string representing the attributes of the LDAP client (divided via ';').
    ///
    char* attributes;
}
ldap_client_t;

///
/// @brief Fetches the LDAP client parameters from directory server resources.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @param client Pointer to an empty ldap_client_t variable.
/// @return
///     - FETCHED_CLIENT_PARAMETERS, when all of the LDAP client parameters have been fetched successfully.
///     - Respective fetch error:
///         a) when plugin failed to retrieve the DN of the LDAP client,
///         b) when plugin failed to retrieve the roles of the LDAP client,
///         c) when plugin failed to retrieve the groups of the LDAP client,
///         d) when plugin failed to retrieve the attributes of the LDAP client.
///
bind_request_status_t fetch_ldap_client_parameters(Slapi_PBlock* block, ldap_client_t* client);

///
/// @brief Disposes the resources allocated for the LDAP client parameters.
/// @param client Pointer to a populated ldap_client_t variable.
///
void dispose_ldap_client_parameters(ldap_client_t* client);

#endif  // LDAP_CLIENT_H_
