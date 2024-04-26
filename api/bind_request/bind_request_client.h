#ifndef BIND_REQUEST_CLIENT_H_
#define BIND_REQUEST_CLIENT_H_

#include "bind_request_state.h"
#include <dirsrv/slapi-plugin.h>

///
/// @brief Represents the LDAP client attributes.
///
typedef struct
{
    ///
    /// @brief DN (Distinguished Name) that idetifies the LDAP client within directory server structure.
    ///
    char* dn;

    ///
    /// @brief Roles that are assigned to the LDAP client (divided by ';').
    ///
    char* roles;

    ///
    /// @brief Groups that are assigned to the LDAP client (divided by ';').
    ///
    char* groups;

    ///
    /// @brief Other attributes that are assigned to the LDAP client (divided by ';').
    ///
    char* attributes;
}
bind_request_client_t;

///
/// @brief Fetches the bind request client parameters from directory server.
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param client Pointer to bind_request_client_t variable that stores the bind request client parameters.
/// @return
///     - FETCHED_PARAMETERS, when all of the bind request client parameters were successfully fetched.
///     - CLIENT_DN_FETCH_FAILURE, when directory server did not return client DN.
///     - CLIENT_ROLES_FETCH_FAILURE, when directory server did not return client roles.
///     - CLIENT_GROUPS_FETCH_FAILURE, when directory server did not return client groups.
///     - CLIENT_ATTRIBUTES_FETCH_FAILURE, when directory server did not return client attributes.
///
bind_request_state_t fetch_bind_request_client_parameters(Slapi_PBlock* block, bind_request_client_t* client);

///
/// @brief Disposes the parameters allocated for the bind request client parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request client parameters.
///
void dispose_bind_request_client_parameters(bind_request_client_t* client);

#endif  // BIND_REQUEST_CLIENT_H_
