#include "aci_rule_operation_provider.h"

static bool after(const aci_rule_operand_t* operands, const bind_request_t* request)
{
    return 0;
}

static bool before(const aci_rule_operand_t* operands, const bind_request_t* request)
{
    return 0;
}

static bool between(const aci_rule_operand_t* operands, const bind_request_t* request)
{
    return 0;
}

aci_rule_operation_t get_time_of_day_operation(aci_rule_operation_type_t operation)
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
