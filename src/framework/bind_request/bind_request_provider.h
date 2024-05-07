#ifndef GATEKEEPER_BIND_REQUEST_PROVIDER_H
#define GATEKEEPER_BIND_REQUEST_PROVIDER_H

#include <dirsrv/slapi-plugin.h>
#include "bind_request.h"
#include "bind_request_status.h"

bind_request_status_t fetch_bind_request_parameters(Slapi_PBlock* block, bind_request_t* request);

void dispose_bind_request_parameters(bind_request_t* request);

#endif  // GATEKEEPER_BIND_REQUEST_PROVIDER_H
