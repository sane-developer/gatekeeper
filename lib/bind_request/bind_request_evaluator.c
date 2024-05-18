#include "bind_request_evaluator.h"
#include "bind_request_resolver.h"

static bool has_applied_rule(Slapi_PBlock* block, aci_rule_linked_list_t* rule, bind_request_t* request)
{
    return true;
}

static bool has_triggered_rule(Slapi_PBlock* block, aci_rule_linked_list_t* rule, bind_request_t* request)
{
    return true;
}

bool has_triggered_any_grant_rules(Slapi_PBlock* block, aci_rule_linked_list_t* rules, bind_request_t* request)
{
    return true;
}

bool has_triggered_any_deny_rules(Slapi_PBlock* block, aci_rule_linked_list_t* rules, bind_request_t* request)
{
    return true;
}

bind_request_status_t grant_bind_request(bind_request_t* request)
{
    dispose_bind_request_parameters(request);

    return REQUEST_GRANTED;
}

bind_request_status_t deny_bind_request(bind_request_t* request)
{
    dispose_bind_request_parameters(request);

    return REQUEST_DENIED;
}
