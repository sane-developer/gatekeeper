#include "aci_rules_evaluator.h"

bind_request_state_t satisfies_grant_aci_rules(const aci_rules_t* rules, bind_request_t* request)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        aci_rule_t* rule = rules->items[i];

        if (!has_applied_aci_rule(rule, request))
        {
            continue;
        }

        if (!has_triggered_aci_rule(rule, request))
        {
            // TODO: Set note to triggered bind rule label.

            return REQUEST_DENIED;
        }
    }

    return SATISFIED_GRANT_ACI_RULES;
}

bind_request_state_t satisfies_deny_aci_rules(const aci_rules_t* rules, bind_request_t* request)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        aci_rule_t* rule = rules->items[i];

        if (!has_applied_aci_rule(rule, request))
        {
            continue;
        }

        if (has_triggered_aci_rule(rule, request))
        {
            // TODO: Set note to triggered bind rule label.

            return REQUEST_DENIED;
        }
    }

    return SATISFIED_DENY_ACI_RULES;
}
