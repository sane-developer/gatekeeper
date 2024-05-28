#include "aci_rule_evaluator.h"
#include "aci_rule_resolver.h"

static bool has_satisfied_operation(aci_rule_operation_t* operation, bind_request_t* request)
{
    aci_rule_operation_handler_t handler = resolve_operation_for_operand(operation->operation_type, operation->operand_type);

    return !handler || handler(operation->operands, request);
}

static bool has_satisfied_condition(aci_rule_condition_t* condition, bind_request_t* request)
{
    bool condition_state = false;

    bool subcondition_state = true;

    bool should_skip_to_next_or_operator = false;

    bool should_accumulate_condition_state = true;

    bool should_accumulate_subcondition_state = false;

    for (size_t i = 0; i < OPERATIONS_LIMIT; ++i)
    {
        aci_rule_operation_t* operation = &condition->operations[i];

        if (should_skip_to_next_or_operator)
        {
            if (operation->operator_type == OR)
            {
                subcondition_state = true;

                should_skip_to_next_or_operator = false;
            }

            continue;
        }

        if (should_accumulate_condition_state)
        {
            if (operation->operator_type == AND)
            {
                subcondition_state &= has_satisfied_operation(operation, request);

                if (!subcondition_state)
                {
                    should_skip_to_next_or_operator = true;
                }

                should_accumulate_condition_state = false;

                should_accumulate_subcondition_state = true;

                continue;
            }

            condition_state |= has_satisfied_operation(operation, request);

            if (condition_state)
            {
                return true;
            }

            continue;
        }

        if (should_accumulate_subcondition_state)
        {
            subcondition_state &= has_satisfied_operation(operation, request);

            if (!subcondition_state)
            {
                should_skip_to_next_or_operator = true;
            }

            if (operation->operator_type == OR || operation->operator_type == TERMINATE)
            {
                condition_state |= subcondition_state;

                if (condition_state)
                {
                    return true;
                }

                subcondition_state = true;

                should_skip_to_next_or_operator = false;

                should_accumulate_subcondition_state = false;

                should_accumulate_condition_state = true;
            }
        }
    }

    return condition_state;
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
        if (!has_satisfied_condition(&rule->satisfy[i], request))
        {
            return true;
        }
    }

    return false;
}
