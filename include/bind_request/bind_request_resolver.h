#ifndef BIND_REQUEST_RESOLVER_H
#define BIND_REQUEST_RESOLVER_H

#include "bind_request.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

bool resolve_bind_request_parameters(
    Slapi_PBlock* block,
    bind_request_t* request
);

void dispose_bind_request_parameters(
    bind_request_t* request
);

#endif  // BIND_REQUEST_RESOLVER_H
