#include "aci_rule_operation_provider.h"

static bool equals(aci_rule_operand_value_t* values, bind_request_t* request)
{
    return true;
}

static bool matches(aci_rule_operand_value_t* values, bind_request_t* request)
{
    return true;
}

static bool range(aci_rule_operand_value_t* values, bind_request_t* request)
{
    return true;
}

static bool any_of(aci_rule_operand_value_t* values, bind_request_t* request)
{
    return true;
}

aci_rule_operation_t get_operation_for_ip_operand(aci_rule_operation_type_t operation)
{
    switch (operation)
    {
        case EQUALS:
            return equals;
        case MATCHES:
            return matches;
        case RANGE:
            return range;
        case ANY_OF:
            return any_of;
        default:
            return NULL;
    }
}
