#include "aci_rule_resolver.h"

static bool equals(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

static bool matches(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

static bool starts_with(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

static bool ends_with(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

aci_rule_operation_handler_t resolve_operation_for_dn_operand(aci_rule_operation_type_t operation_type)
{
    switch (operation_type)
    {
        case EQUALS:
            return equals;
        case MATCHES:
            return matches;
        case STARTS_WITH:
            return starts_with;
        case ENDS_WITH:
            return ends_with;
        default:
            return NULL;
    }
}
