#ifndef BIND_REQUEST_EVALUATOR_H
#define BIND_REQUEST_EVALUATOR_H

#include "aci_rule.h"
#include "bind_request.h"
#include "bind_request_status.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

bool has_triggered_any_grant_rules(
    bind_request_t* request,
    aci_rule_linked_list_t* rules,
    aci_rule_identity_t* rule_identity
);

bool has_triggered_any_deny_rules(
    bind_request_t* request,
    aci_rule_linked_list_t* rules,
    aci_rule_identity_t* rule_identity
);

bind_request_status_t grant_bind_request(
    Slapi_PBlock* block,
    bind_request_t* request
);

bind_request_status_t deny_bind_request(
    Slapi_PBlock* block,
    bind_request_t* request,
    aci_rule_identity_t* rule_identity
);

#endif  // BIND_REQUEST_EVALUATOR_H
