#ifndef BIND_REQUEST_RESOLVER_H
#define BIND_REQUEST_RESOLVER_H

#include "bind_request.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

typedef enum
{
    FAILED_TO_RESOLVE_CLIENT_DN,

    FAILED_TO_RESOLVE_CLIENT_IP,

    FAILED_TO_RESOLVE_CLIENT_DNS,

    FAILED_TO_RESOLVE_CLIENT_GROUPS,

    FAILED_TO_RESOLVE_CLIENT_ATTRIBUTES,

    FAILED_TO_FETCH_REQUEST_DATETIME
}
bind_request_resolver_error_t;

typedef struct
{
    Slapi_PBlock* block;

    bind_request_resolver_error_t error;
}
unresolved_bind_request_parameter_event_args_t;

void on_unresolved_bind_request_parameter(
    unresolved_bind_request_parameter_event_args_t args
);

bool has_resolved_bind_request_parameters(
    Slapi_PBlock* block,
    bind_request_t* request
);

void dispose_bind_request_parameters(
    bind_request_t* request
);

#endif  // BIND_REQUEST_RESOLVER_H
