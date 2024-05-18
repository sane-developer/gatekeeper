#include "bind_request_evaluator.h"
#include "bind_request_resolver.h"

static bool has_applied_rule(Slapi_PBlock* block, aci_rule_t* rule, bind_request_t* request)
{
    return true;
}

static bool has_triggered_rule(Slapi_PBlock* block, aci_rule_t* rule, bind_request_t* request)
{
    return true;
}

static bool has_triggered_any_grant_rule(Slapi_PBlock* block, aci_rule_t* rules, bind_request_t* request)
{
    return true;
}

static bool has_triggered_any_deny_rule(Slapi_PBlock* block, aci_rule_t* rules, bind_request_t* request)
{
    return true;
}

static bind_request_status_t grant_bind_request(bind_request_t* request)
{
    dispose_bind_request_parameters(request);

    return REQUEST_GRANTED;
}

static bind_request_status_t deny_bind_request(bind_request_t* request)
{
    dispose_bind_request_parameters(request);

    return REQUEST_DENIED;
}

bind_request_status_t evaluate_bind_request(Slapi_PBlock* block, aci_rule_t* grant_rules, aci_rule_t* deny_rules)
{
    bind_request_t request = {0};

    if (!has_resolved_bind_request_parameters(block, &request))
    {
        return deny_bind_request(&request);
    }

    if (has_triggered_any_deny_rule(block, deny_rules, &request))
    {
        return deny_bind_request(&request);
    }

    if (has_triggered_any_grant_rule(block, grant_rules, &request))
    {
        return deny_bind_request(&request);
    }

    return grant_bind_request(&request);
}
