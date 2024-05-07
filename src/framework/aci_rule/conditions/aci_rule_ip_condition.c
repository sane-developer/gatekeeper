#include "aci_rule_conditions.h"

static bool equals(const aci_rule_condition_operands_t* operands, const PRNetAddr* ip)
{
    return 0;
}

static bool range(const aci_rule_condition_operands_t* operands, const PRNetAddr* ip)
{
    return 0;
}

static bool in(const aci_rule_condition_operands_t* operands, const PRNetAddr* ip)
{
    return 0;
}

bool satisfies_ip_condition(const aci_rule_condition_t* condition, const PRNetAddr* ip)
{
    switch (condition->operation)
    {
        case EQUALS:
            return equals(condition->operands, ip);
        case RANGE:
            return range(condition->operands, ip);
        case IN:
            return in(condition->operands, ip);
        default:
            return false;
    }
}
