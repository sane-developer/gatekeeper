#ifndef GATEKEEPER_BIND_REQUEST_EVENTS_H
#define GATEKEEPER_BIND_REQUEST_EVENTS_H

#include <dirsrv/slapi-plugin.h>
#include "bind_request.h"
#include "bind_request_status.h"

void on_granted_bind_request(Slapi_PBlock* block, bind_request_t* request);

void on_denied_bind_request(Slapi_PBlock* block, bind_request_t* request, bind_request_error_t error);

#endif  // GATEKEEPER_BIND_REQUEST_EVENTS_H
