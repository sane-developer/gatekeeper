#ifndef BIND_REQUEST_CLIENT_H_
#define BIND_REQUEST_CLIENT_H_

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
/// @brief Determines whether the specified DN matches the one of the client.
/// 
/// @param client Pointer to a bind_request_client_t variable that stores the information about LDAP client.
/// @param dn Pointer to a string that contains a DN to match against.
/// 
/// @return
///     - 1, when the DNs are equal.
///     - 0, otherwise.
///
int matches_client_dn(const bind_request_client_t* const client, const char* const dn);

///
/// @brief Determines whether the LDAP client belongs to the specified role.
/// 
/// @param client Pointer to a bind_request_client_t variable that stores the information about LDAP client.
/// @param role_name Pointer to a string that contains the name of the role to check against.
/// 
/// @return
///     - 1, when the LDAP client belongs to the specified role.
///     - 0, otherwise.
///
int matches_client_roles(const bind_request_client_t* const client, const char* const role_name);

///
/// @brief Determines whether the LDAP client belongs to the specified group.
/// 
/// @param client Pointer to a bind_request_client_t variable that stores the information about LDAP client.
/// @param group_name Pointer to a string that contains the name of the group to check against.
/// 
/// @return
///     - 1, when the LDAP client belongs to the specified group.
///     - 0, otherwise .
///
int matches_client_groups(const bind_request_client_t* const client, const char* const group_name);

///
/// @brief Determines whether the LDAP client has the specified attribute assigned.
/// 
/// @param client Pointer to a bind_request_client_t variable that stores the information about LDAP client.
/// @param attribute Pointer to a string that contains the attribute to check against.
/// 
/// @return
///     - 1, when the LDAP client has the specified attribute assigned.
///     - 0, otherwise.
///
int matches_client_attributes(const bind_request_client_t* const client, const char* const attribute);

#endif  // BIND_REQUEST_CLIENT_H_
