#include "bind_request_evaluator.h"
#include "bind_request_event_dispatcher.h"
#include "bind_request_resolver.h"

static bool has_applied_rule(bind_request_t* request, aci_rule_t* rule)
{
    return true;
}

static bool has_triggered_rule(bind_request_t* request, aci_rule_t* rule)
{
    return true;
}

bool has_triggered_any_grant_rules(bind_request_t* request, aci_rule_linked_list_t* rules, aci_rule_identity_t* rule_identity)
{
    return true;
}

bool has_triggered_any_deny_rules(bind_request_t* request, aci_rule_linked_list_t* rules, aci_rule_identity_t* rule_identity)
{
    return true;
}

bind_request_status_t signal_granted_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    on_granted_bind_request((granted_bind_request_event_args_t) {
        .block = block,
        .request = request
    });

    dispose_bind_request_parameters(request);

    return REQUEST_GRANTED;
}

bind_request_status_t signal_denied_bind_request(Slapi_PBlock* block, bind_request_t* request, aci_rule_identity_t* rule_identity)
{
    on_denied_bind_request((denied_bind_request_event_args_t) {
        .block = block,
        .request = request,
        .rule_label = rule_identity->rule_label,
        .condition_label = rule_identity->condition_label
    });

    dispose_bind_request_parameters(request);

    return REQUEST_DENIED;
}
