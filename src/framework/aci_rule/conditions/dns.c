#include "aci_rule_condition.h"

static bool equals(const aci_rule_operands_t* operands, const PRNetAddr* dns)
{
    return 0;
}

static bool in(const aci_rule_operands_t* operands, const PRNetAddr* dns)
{
    return 0;
}

dns_operation get_dns_operation(aci_rule_operation_t operation)
{
    switch (operation)
    {
        case EQUALS:
            return equals;
        case IN:
            return in;
        default:
            return NULL;
    }
}
