#ifndef BIND_REQUEST_EVENT_HANDLERS_H
#define BIND_REQUEST_EVENT_HANDLERS_H

#include "bind_request.h"
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
///
void on_denied_bind_request(Slapi_PBlock* block, const bind_request_t* request);

#endif  // BIND_REQUEST_EVENT_HANDLERS_H
