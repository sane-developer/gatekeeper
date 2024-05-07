#include "aci_rule_conditions.h"

static bool all(const aci_rule_condition_operands_t* operands, const char** groups)
{
    return 0;
}

static bool any(const aci_rule_condition_operands_t* operands, const char** groups)
{
    return 0;
}

bool satisfies_groups_condition(const aci_rule_condition_t* condition, const char** groups)
{
    switch (condition->operation)
    {
        case ALL:
            return all(condition->operands, groups);
        case ANY:
            return any(condition->operands, groups);
        default:
            return false;
    }
}
