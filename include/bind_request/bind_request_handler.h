#ifndef BIND_REQUEST_HANDLER_H
#define BIND_REQUEST_HANDLER_H

#include "aci_rule.h"
#include "bind_request.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

bool resolve_bind_request_parameters(
    Slapi_PBlock* block,
    bind_request_t* request
);

bool evaluate_against_deny_rules(
    Slapi_PBlock* block,
    aci_rule_linked_list_t* rules,
    bind_request_t* request
);

bool evaluate_against_grant_rules(
    Slapi_PBlock* block,
    aci_rule_linked_list_t* rules,
    bind_request_t* request
);

#endif  // BIND_REQUEST_HANDLER_H
