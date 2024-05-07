#include "aci_rule_condition.h"

static bool all(const aci_rule_operands_t* operands, const char** roles)
{
    return 0;
}

static bool any(const aci_rule_operands_t* operands, const char** roles)
{
    return 0;
}

roles_operation get_attributes_operation(aci_rule_operation_t operation)
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
