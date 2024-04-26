#include "aci_rule.h"

static int has_satisfied_aci_rule_conditions(const aci_rule_conditions_t* conditions, const bind_request_t* request)
{
    for (size_t i = 0; i < conditions->count; ++i)
    {
        aci_rule_condition_t* condition = conditions->items[i];

        // TODO: Implement condition logic.
    }

    return 1;
}

int has_applied_aci_rule(const aci_rule_t* rule, const bind_request_t* request)
{
    return has_satisfied_aci_rule_conditions(rule->apply, request);
}

int has_triggered_aci_rule(const aci_rule_t* rule, const bind_request_t* request)
{
    return has_satisfied_aci_rule_conditions(rule->bind, request);
}
