#ifndef BIND_REQUEST_EVALUATOR_H
#define BIND_REQUEST_EVALUATOR_H

#include "aci_rule.h"
#include "bind_request.h"
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

void on_granted_bind_request(
    granted_bind_request_event_args_t args
);

void on_denied_bind_request(
    denied_bind_request_event_args_t args
);

bind_request_status_t evaluate_bind_request(
    Slapi_PBlock* block,
    aci_rule_t* grant_rules,
    aci_rule_t* deny_rules
);

#endif  // BIND_REQUEST_EVALUATOR_H
