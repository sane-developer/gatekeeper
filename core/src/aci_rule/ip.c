#include "aci_rule.h"

static bool between(const PRNetAddr* ip, const aci_rule_operands_t* operands)
{
    return operands->items[0].ip <= ip->inet.ip <= operands->items[1].ip;
}

static bool equals(const PRNetAddr* ip, const aci_rule_operands_t* operands)
{
    return operands->items[0].ip == ip->inet.ip;
}

bool has_satisfied_ip_operation(const PRNetAddr* ip, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case BETWEEN:
            return between(ip, &operation->operands);
        case EQUALS:
            return equals(ip, &operation->operands);
        default:
            return false;
    }
}
