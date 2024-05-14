#include "aci_rule_operation_provider.h"

static bool all_of(aci_rule_operand_value_t* operands, bind_request_t* request)
{
    return true;
}

static bool any_of(aci_rule_operand_value_t* operands, bind_request_t* request)
{
    return true;
}

aci_rule_operation_t get_operation_for_group_operand(aci_rule_operation_type_t operation)
{
    switch (operation)
    {
        case ALL_OF:
            return all_of;
        case ANY_OF:
            return any_of;
        default:
            return NULL;
    }
}
