#include "aci_rule_resolver.h"

static bool equals(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

static bool matches(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

static bool range(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

aci_rule_operation_handler_t resolve_operation_for_ip_operand(aci_rule_operation_type_t operation_type)
{
    switch (operation_type)
    {
        case EQUALS:
            return equals;
        case MATCHES:
            return matches;
        case RANGE:
            return range;
        default:
            return NULL;
    }
}
