#include "aci_rule_resolver.h"

static bool after(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

static bool before(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

static bool between(aci_rule_operand_t* operands, bind_request_t* request)
{
    return false; // TODO: Implement.
}

aci_rule_operation_handler_t resolve_operation_for_time_operand(aci_rule_operation_type_t operation_type)
{
    switch (operation_type)
    {
        case AFTER:
            return after;
        case BEFORE:
            return before;
        case BETWEEN:
            return between;
        default:
            return NULL;
    }
}
