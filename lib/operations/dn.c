#include "aci_rule_operation_provider.h"

static bool equals(aci_rule_operand_value_t* operands, bind_request_t* request)
{
    return true;
}

static bool matches(aci_rule_operand_value_t* operands, bind_request_t* request)
{
    return true;
}

static bool starts_with(aci_rule_operand_value_t* operands, bind_request_t* request)
{
    return true;
}

static bool ends_with(aci_rule_operand_value_t* operands, bind_request_t* request)
{
    return true;
}

static bool any_of(aci_rule_operand_value_t* operands, bind_request_t* request)
{
    return true;
}

aci_rule_operation_t get_operation_for_dn_operand(aci_rule_operation_type_t operation)
{
    switch (operation)
    {
        case EQUALS:
            return equals;
        case MATCHES:
            return matches;
        case STARTS_WITH:
            return starts_with;
        case ENDS_WITH:
            return ends_with;
        case ANY_OF:
            return any_of;
        default:
            return NULL;
    }
}
