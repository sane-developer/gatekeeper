#include "aci_rule_conditions.h"

static bool all(const aci_rule_condition_operands_t* operands, const char** attributes)
{
    return 0;
}

static bool any(const aci_rule_condition_operands_t* operands, const char** attributes)
{
    return 0;
}

bool satisfies_attributes_condition(const aci_rule_condition_t* condition, const char** attributes)
{
    switch (condition->operation)
    {
        case ALL:
            return all(condition->operands, attributes);
        case ANY:
            return any(condition->operands, attributes);
        default:
            return false;
    }
}
