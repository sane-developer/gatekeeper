#include "aci_rule_evaluator.h"
#include "bind_request_event_dispatcher.h"
#include "bind_request_handler.h"
#include "bind_request_resolver.h"
#include "bind_request_resolver_errors.h"

bool resolve_bind_request_parameters(Slapi_PBlock* block, bind_request_t* request)
{
    if (!fetch_client_dn(block, request->dn))
    {
        signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_DN);

        return false;
    }

    if (!fetch_client_ip(block, request->ip))
    {
        signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_IP);

        return false;
    }

    if (!fetch_client_dns(block, request->dns))
    {
        signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_DNS);

        return false;
    }

    if (!fetch_client_groups(block, request->groups))
    {
        signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_GROUPS);

        return false;
    }

    if (!fetch_client_attributes(block, request->attributes))
    {
        signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_ATTRIBUTES);

        return false;
    }

    fetch_request_datetime(&request->datetime);

    return true;
}

bool evaluate_against_grant_rules(Slapi_PBlock* block, aci_rule_linked_list_t* head, bind_request_t* request)
{
    for (aci_rule_t* rule = head; rule != NULL; rule = rule->next)
    {
        if (has_applied_rule(block, rule, request) && !has_triggered_rule(block, rule, request))
        {
            return false;
        }
    }

    return true;
}

bool evaluate_against_deny_rules(Slapi_PBlock* block, aci_rule_linked_list_t* head, bind_request_t* request)
{
    for (aci_rule_t* rule = head; rule != NULL; rule = rule->next)
    {
        if (has_applied_rule(block, rule, request) && has_triggered_rule(block, rule, request))
        {
            return false;
        }
    }

    return true;
}
