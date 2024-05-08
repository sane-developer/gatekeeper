#include "aci_rule_operation_provider.h"

static bool equals(const aci_rule_operand_t* operands, const bind_request_t* request)
{
    return 0;
}

static bool range(const aci_rule_operand_t* operands, const bind_request_t* request)
{
    return 0;
}

static bool in(const aci_rule_operand_t* operands, const bind_request_t* request)
{
    return 0;
}

aci_rule_operation get_ip_operation(aci_rule_operation_t operation)
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
