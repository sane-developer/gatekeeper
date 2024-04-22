#ifndef BIND_REQUEST_H_
#define BIND_REQUEST_H_

#include "bind_request_client.h"
#include "bind_request_connection.h"
#include "slapi-plugin.h"

///
/// @brief Represents the status of processed bind request.
///
typedef enum
{
    ///
    /// @brief Value indicating that bind request has been granted.
    ///
    REQUEST_GRANTED = 0,

    ///
    /// @brief Value indicating that bind request has been denied.
    ///
    REQUEST_DENIED = 1
}
bind_request_evaluation_t;

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
    /// @brief Pointer to a string that holds the reason behind the evaluation.
    ///
    char* note;
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
///     - Writes a log about granted bind request.
///     - Disposes bind_request_t variable resources.
///     - Sends bind operation denied ldap code to the LDAP client.
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
///     - Writes a log about denied bind request.
///     - Disposes bind_request_t variable resources.
///     - Sends bind operation denied ldap code to the LDAP client.
///
bind_request_evaluation_t deny_bind_request(const Slapi_PBlock* const block, bind_request_t* request);

#endif  // BIND_REQUEST_H_
