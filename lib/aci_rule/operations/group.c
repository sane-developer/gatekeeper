#include "aci_rule_operation_resolver.h"

static bool all_of(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

static bool any_of(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

aci_rule_operation_handler_t resolve_operation_for_group_operand(aci_rule_operation_type_t operation_type)
{
    switch (operation_type)
    {
        case ALL_OF:
            return all_of;
        case ANY_OF:
            return any_of;
        default:
            return NULL;
    }
}
