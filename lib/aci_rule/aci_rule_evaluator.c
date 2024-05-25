#include "aci_rule_evaluator.h"
#include "aci_rule_resolver.h"

static bool has_satisfied_operation(aci_rule_operation_t* operation, bind_request_t* request)
{
    aci_rule_operation_handler_t handler = resolve_operation_for_operand(operation->operation_type, operation->operand_type);

    return !handler || handler(operation->operands, request);
}

static bool has_satisfied_condition(aci_rule_condition_t* condition, bind_request_t* request)
{
    return false; // TODO: Implement.
}

bool has_applied_rule(Slapi_PBlock* block, aci_rule_t* rule, bind_request_t* request)
{
    for (size_t i = 0; i < CONDITIONS_LIMIT; ++i)
    {
        if (has_satisfied_condition(&rule->exclude[i], request))
        {
            return false;
        }
    }

    for (size_t i = 0; i < CONDITIONS_LIMIT; ++i)
    {
        if (!has_satisfied_condition(&rule->apply[i], request))
        {
            return false;
        }
    }

    return true;
}

bool has_triggered_rule(Slapi_PBlock* block, aci_rule_t* rule, bind_request_t* request)
{
    for (size_t i = 0; i < CONDITIONS_LIMIT; ++i)
    {
        if (!has_satisfied_condition(&rule->bind[i], request))
        {
            return true;
        }
    }

    return false;
}
