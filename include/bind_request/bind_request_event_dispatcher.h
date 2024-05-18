#ifndef BIND_REQUEST_EVENT_DISPATCHER_H
#define BIND_REQUEST_EVENT_DISPATCHER_H

#include "bind_request.h"
#include "bind_request_resolver_error.h"
#include <dirsrv/slapi-plugin.h>

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

    char* rule_label;

    char* condition_label;
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

#endif  // BIND_REQUEST_EVENT_DISPATCHER_H
