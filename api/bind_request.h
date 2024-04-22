#ifndef BIND_REQUEST_H_
#define BIND_REQUEST_H_

#include "bind_request_client.h"
#include "bind_request_connection.h"
#include "bind_request_status.h"
#include "slapi-plugin.h"

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
    /// @brief Pointer to a container that holds information about bind request evaluation status.
    ///
    bind_request_status_t* status;
}
bind_request_t;

///
/// @brief Sets up the bind_request_t variable with necessary data from directory server and system resources.
///
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request parameters.
///
/// @return
///     - REQUEST_GRANTED, when all of bind request parameters have been successfully set.
///     - REQUEST_DENIED, when any of the bind request parameters could not be set.
///
bind_request_evaluation_t setup_bind_request(const Slapi_PBlock* const block, bind_request_t* const request);

///
/// @brief Instructs the directory server to grant the bind request issued by the LDAP client.
///
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request parameters.
///
/// @return REQUEST_GRANTED.
///
/// @remarks This method contains side-effects:
///     - Sends bind operation denied ldap code,
///     - Writes a log about denied request.
///
bind_request_evaluation_t grant_bind_request(const Slapi_PBlock* const block, bind_request_t* request);

///
/// @brief Instructs the directory server to deny the bind request issued by the LDAP client.
///
/// @param block Pointer to Slapi_PBlock variable that stores the bind operation parameters.
/// @param request Pointer to bind_request_t variable that stores the bind request parameters.
///
/// @return REQUEST_DENIED.
///
/// @remarks This method contains side-effects:
///     - Sends bind operation denied ldap code,
///     - Writes a log about denied request.
///
bind_request_evaluation_t deny_bind_request(const Slapi_PBlock* const block, bind_request_t* request);

#endif  // BIND_REQUEST_H_
