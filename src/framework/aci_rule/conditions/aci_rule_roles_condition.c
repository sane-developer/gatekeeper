#include "aci_rule_conditions.h"

static bool all(const aci_rule_condition_operands_t* operands, const char** roles)
{
    return 0;
}

static bool any(const aci_rule_condition_operands_t* operands, const char** roles)
{
    return 0;
}

bool satisfies_roles_condition(const aci_rule_condition_t* condition, const char** roles)
{
    switch (condition->operation)
    {
        case ALL:
            return all(condition->operands, roles);
        case ANY:
            return any(condition->operands, roles);
        default:
            return false;
    }
}
