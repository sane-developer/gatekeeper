#ifndef BIND_REQUEST_INITIALIZER_H
#define BIND_REQUEST_INITIALIZER_H

#include "bind_request.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

///
/// @brief
/// @param block
/// @param request
/// @return
///
bool has_fetched_request_parameters(Slapi_PBlock* block, bind_request_t* request);

///
/// @brief
/// @param request
///
void dispose_request_parameters(bind_request_t* request);

#endif  // BIND_REQUEST_INITIALIZER_H
