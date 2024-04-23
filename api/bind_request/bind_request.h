#ifndef BIND_REQUEST_H_
#define BIND_REQUEST_H_

#include <dirsrv/slapi-plugin.h>
#include "bind_request_client.h"
#include "bind_request_connection.h"

///
/// @brief Represents the status of processed bind request.
///
typedef enum
{
    ///
    /// @brief Value indicating that request has been granted.
    ///
    REQUEST_GRANTED = 0,

    ///
    /// @brief Value indicating that request has been denied.
    ///
    REQUEST_DENIED = 1,

    ///
    /// @brief Value indicating that plugin could not fetch client DN.
    ///
    CLIENT_DN_FETCH_FAILURE = 2,

    ///
    /// @brief Value indicating that plugin could not fetch client roles.
    ///
    CLIENT_ROLES_FETCH_FAILURE = 3,

    ///
    /// @brief Value indicating that plugin could not fetch client groups.
    ///
    CLIENT_GROUPS_FETCH_FAILURE = 4,

    ///
    /// @brief Value indicating that plugin could not fetch client attributes.
    ///
    CLIENT_ATTRIBUTES_FETCH_FAILURE = 5,

    ///
    /// @brief Value indicating that plugin could not fetch client IPv4 address.
    ///
    CLIENT_IP_FETCH_FAILURE = 6,

    ///
    /// @brief Value indicating that plugin could not fetch DNS IPv4 address.
    ///
    CLIENT_DNS_FETCH_FAILURE = 7,

    ///
    /// @brief Value indicating that plugin could not fetch authentication method.
    ///
    CLIENT_AUTH_FETCH_FAILURE = 8,

    ///
    /// @brief Value indicating that request parameters have been successfully fetched.
    ///
    PARAMETERS_FETCH_SUCCESS = 9,

    ///
    /// @brief Value indicating that request did not trigger any of the applied deny ACI rules.
    ///
    SATISFIED_DENY_ACI_RULES = 10,

    ///
    /// @brief Value indicating that request triggered all of the applied grant ACI rules.
    ///
    SATISFIED_GRANT_ACI_RULES = 11
}
bind_request_state_t;

///
/// @brief Represents the bind request issued by the LDAP client.
///
typedef struct
{
    ///
    /// @brief Pointer to a container that holds information about the LDAP client.
    ///
    bind_request_client_t* client;

    ///
    /// @brief Pointer to a container that holds information about the LDAP client connection.
    ///
    bind_request_connection_t* connection;

    ///
    /// @brief Pointer to a string that holds the additional information behind the evaluation.
    ///
    char* note;
}
bind_request_t;

///
/// @brief Fetches the bind request parameters from directory server and system resources.
///
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request parameters.
///
/// @return
///     - PARAMETERS_FETCH_SUCCESS, when all of the bind request parameters were successfully fetched.
///     - {RESOURCE_NAME}_FETCH_FAILURE, when the {RESOURCE_NAME} could not be fetched.
///
bind_request_state_t fetch_bind_request_parameters(Slapi_PBlock* block, bind_request_t* const request);

///
/// @brief Instructs the directory server to grant the bind request issued by the LDAP client.
///
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request parameters.
///
/// @return REQUEST_GRANTED.
///
/// @remarks This method contains side-effects:
///     - Writes a log about granted bind request.
///     - Disposes bind_request_t variable resources.
///     - Sends bind operation denied ldap code to the LDAP client.
///
bind_request_state_t grant_bind_request(Slapi_PBlock* block, bind_request_t* request);

///
/// @brief Instructs the directory server to deny the bind request issued by the LDAP client.
///
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request parameters.
/// @param state Numerical value indicating the main cause of denial of the bind request.
///
/// @return REQUEST_DENIED.
///
/// @remarks This method contains side-effects:
///     - Writes a log about denied bind request.
///     - Disposes bind_request_t variable resources.
///     - Sends bind operation denied ldap code to the LDAP client.
///
bind_request_state_t deny_bind_request(Slapi_PBlock* block, bind_request_t* request, bind_request_state_t state);

#endif  // BIND_REQUEST_H_
