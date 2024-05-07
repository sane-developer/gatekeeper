#include "aci_rule_conditions.h"

static bool equals(const aci_rule_condition_operands_t* operands, const PRNetAddr* dns)
{
    return 0;
}

static bool in(const aci_rule_condition_operands_t* operands, const PRNetAddr* dns)
{
    return 0;
}

bool satisfies_dns_condition(const aci_rule_condition_t* condition, const PRNetAddr* dns)
{
    switch (condition->operation)
    {
        case EQUALS:
            return equals(condition->operands, dns);
        case IN:
            return in(condition->operands, dns);
        default:
            return false;
    }
}
