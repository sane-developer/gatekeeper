#ifndef BIND_REQUEST_EVENT_DISPATCHER_H
#define BIND_REQUEST_EVENT_DISPATCHER_H

#include "bind_request.h"
#include "bind_request_resolver_errors.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

typedef struct
{
    Slapi_PBlock* block;

    bind_request_t* request;
}
granted_bind_request_event_args_t;

typedef struct
{
    Slapi_PBlock* block;

    bind_request_t* request;
}
denied_bind_request_event_args_t;

typedef struct
{
    Slapi_PBlock* block;

    bind_request_resolver_error_t error;
}
unresolved_bind_request_parameter_event_args_t;

void on_granted_bind_request(
    granted_bind_request_event_args_t args
);

void on_denied_bind_request(
    denied_bind_request_event_args_t args
);

void on_unresolved_bind_request_parameter(
    unresolved_bind_request_parameter_event_args_t args
);

void signal_granted_bind_request(
    Slapi_PBlock* block,
    bind_request_t* request
);

void signal_denied_bind_request(
    Slapi_PBlock* block,
    bind_request_t* request
);

void signal_unresolved_bind_request_parameter(
    Slapi_PBlock* block,
    bind_request_resolver_error_t error
);

#endif  // BIND_REQUEST_EVENT_DISPATCHER_H
