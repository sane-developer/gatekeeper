#ifndef BIND_REQUEST_EVENTS_H
#define BIND_REQUEST_EVENTS_H

#include "bind_request.h"
#include "bind_request_status.h"
#include <dirsrv/slapi-plugin.h>

///
/// @brief
/// @param block
/// @param request
///
void on_granted_bind_request(Slapi_PBlock* block, const bind_request_t* request);

///
/// @brief
/// @param block
/// @param request
/// @param error
///
void on_denied_bind_request(Slapi_PBlock* block, const bind_request_t* request, bind_request_error_t error);

#endif  // BIND_REQUEST_EVENTS_H
