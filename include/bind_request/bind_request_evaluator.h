#ifndef BIND_REQUEST_EVALUATOR_H
#define BIND_REQUEST_EVALUATOR_H

#include "aci_rule.h"
#include "bind_request.h"
#include "bind_request_status.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

bool has_triggered_any_grant_rules(
    Slapi_PBlock* block,
    aci_rule_linked_list_t* rules,
    bind_request_t* request
);

bool has_triggered_any_deny_rules(
    Slapi_PBlock* block,
    aci_rule_linked_list_t* rules,
    bind_request_t* request
);

bind_request_status_t grant_bind_request(
    bind_request_t* request
);

bind_request_status_t deny_bind_request(
    bind_request_t* request
);

#endif  // BIND_REQUEST_EVALUATOR_H
