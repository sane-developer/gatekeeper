#include "aci_rule_operation_provider.h"

static bool all(const aci_rule_operand_t* operands, const bind_request_t* request)
{
    return 0;
}

static bool any(const aci_rule_operand_t* operands, const bind_request_t* request)
{
    return 0;
}

aci_rule_operation_t get_roles_operation(aci_rule_operation_type_t operation)
{
    switch (operation)
    {
        case ALL:
            return all;
        case ANY:
            return any;
        default:
            return NULL;
    }
}
