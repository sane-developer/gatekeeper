#ifndef GATEKEEPER_BIND_REQUEST_T_H_
#define GATEKEEPER_BIND_REQUEST_T_H_

#include "bind_request_client_t.h"
#include "bind_request_datetime_t.h"

///
/// @brief Represents the bind request issued by the client.
///
typedef struct
{
    ///
    /// @brief The pointer to the client metadata retrieved from the directory server.
    ///
    bind_request_client_t* client;

    ///
    /// @brief The pointer to the datetime metadata retrieved from the system.
    ///
    bind_request_datetime_t* datetime;
}
bind_request_t;

///
/// @brief Sets the bind request metadata based on the information stored in operation block.
/// @param block Pointer to key-value pair container that contains information about operation.
/// @param request Pointer to bind request metadata container.
/// @return
///     - 1, when the bind request metadata is successfully set.
///     - 0, when the any of the metadata fields couldn't be filled.
///
int setup_bind_request(Slapi_PBlock* block, bind_request_t* const request);

///
/// @brief Disposes the metadata allocated for sake of processing the bind request.
/// @param request Pointer to bind request metadata container.
///
void dispose_bind_request(bind_request_t* request);

#endif  // GATEKEEPER_BIND_REQUEST_T_H_
