#ifndef GATEKEEPER_BIND_REQUEST_T_H_
#define GATEKEEPER_BIND_REQUEST_T_H_

#include <dirsrv/slapi-plugin.h>
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
/// @brief Populates the bind request with data retrived from the server.
/// @param block The pointer to the directory server parameter block. 
/// @param request The pointer to the empty bind request.
/// @return 1, when the bind request has been successfully populated; otherwise, 0.
///
int populate_bind_request(Slapi_PBlock* block, bind_request_t* const request);

///
/// @brief Disposes the resources used to populate the bind request.
/// @param request The pointer to the populated bind request.
///
void dispose_bind_request(bind_request_t* request);

#endif  // GATEKEEPER_BIND_REQUEST_T_H_
