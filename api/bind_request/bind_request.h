#ifndef BIND_REQUEST_H_
#define BIND_REQUEST_H_

#include "bind_request_connection.h"
#include "bind_request_client.h"

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
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request parameters.
/// @return
///     - FETCHED_PARAMETERS, when all of the bind request parameters were successfully fetched.
///     - Respective error, otherwise.
///
bind_request_state_t fetch_bind_request_parameters(Slapi_PBlock* block, bind_request_t* request);

///
/// @brief Disposes the parameters allocated for the bind request.
/// @param request Pointer to bind_request_t variable that stores the bind request parameters.
///
void dispose_bind_request_parameters(bind_request_t* request);

#endif  // BIND_REQUEST_H_
