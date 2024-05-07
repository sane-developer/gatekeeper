#ifndef BIND_REQUEST_PROVIDER_H
#define BIND_REQUEST_PROVIDER_H

#include "bind_request.h"
#include "bind_request_status.h"
#include <dirsrv/slapi-plugin.h>

///
/// @brief
/// @param block
/// @param request
/// @return
///
bind_request_status_t fetch_bind_request_parameters(Slapi_PBlock* block, bind_request_t* request);

///
/// @brief
/// @param request
///
void dispose_bind_request_parameters(bind_request_t* request);

#endif  // BIND_REQUEST_PROVIDER_H
