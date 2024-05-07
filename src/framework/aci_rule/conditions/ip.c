#include "aci_rule_condition.h"

static bool equals(const aci_rule_operands_t* operands, const PRNetAddr* ip)
{
    return 0;
}

static bool range(const aci_rule_operands_t* operands, const PRNetAddr* ip)
{
    return 0;
}

static bool in(const aci_rule_operands_t* operands, const PRNetAddr* ip)
{
    return 0;
}

ip_operation get_ip_operation(aci_rule_operation_t operation)
{
    switch (operation)
    {
        case EQUALS:
            return equals;
        case RANGE:
            return range;
        case IN:
            return in;
        default:
            return NULL;
    }
}
