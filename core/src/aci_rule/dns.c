#include "aci_rule.h"

static bool between(const PRNetAddr* dns, const aci_rule_operands_t* operands)
{
    return operands->items[0].integer <= dns->inet.ip && dns->inet.ip <= operands->items[1].integer;
}

static bool equals(const PRNetAddr* dns, const aci_rule_operands_t* operands)
{
    return operands->items[0].integer == dns->inet.ip;
}

bool has_satisfied_dns_operation(const PRNetAddr* dns, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case BETWEEN:
            return between(dns, &operation->operands);
        case EQUALS:
            return equals(dns, &operation->operands);
        default:
            return false;
    }
}
