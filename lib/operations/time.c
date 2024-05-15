#include "aci_rule_operation_provider.h"

static bool after(aci_rule_operand_value_t* values, bind_request_t* request)
{
    return true;
}

static bool before(aci_rule_operand_value_t* values, bind_request_t* request)
{
    return true;
}

static bool between(aci_rule_operand_value_t* values, bind_request_t* request)
{
    return true;
}

aci_rule_operation_t get_operation_for_time_operand(aci_rule_operation_type_t operation)
{
    switch (operation)
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
