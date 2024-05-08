#include "aci_rule_evaluator.h"

static bool has_satisfied_condition(const aci_rule_condition_t* condition, const bind_request_t* request)
{
    bool state = true;

    bool substate = true;

    aci_rule_operator_t operator = AND;

    const struct aci_rule_expression_t* head = condition;

    while (head)
    {
        expression_operation operation = get_expression_operation(head->parameter, head->operation);

        switch (operator)
        {
            case AND:
            {
                if (!substate)
                {
                    break;  // The output will always be 0 at this point. Skip till next OR.
                }

                substate &= operation(head->operands, request);

                break;
            }
            case OR:
            {
                if (substate)
                {
                    return true; // The output will always be 1 at this point.
                }

                substate |= operation(head->operands, request);

                state &= substate;

                substate = true; // The substate must be reset in case the next operation is AND;

                break;
            }
            case TERMINATOR:
            {
                return state & substate; // The end of the evaluation.
            }
        }

        operator = head->operator;

        head = head->next;
    }
}

static bool has_satisfied_any_conditions(const aci_rule_condition_t** conditions, const bind_request_t* request)
{
    for (size_t i = 0; i < MAXIMUM_CONDITIONS_COUNT; ++i)
    {
        const aci_rule_condition_t* condition = conditions[i];

        if (has_satisfied_condition(condition, request))
        {
            return true;
        }
    }

    return false;
}

static bool has_satisfied_all_conditions(const aci_rule_condition_t** conditions, const bind_request_t* request)
{
    for (size_t i = 0; i < MAXIMUM_CONDITIONS_COUNT; ++i)
    {
        const aci_rule_condition_t* condition = conditions[i];

        if (!has_satisfied_condition(condition, request))
        {
            return false;
        }
    }

    return true;
}

bool has_applied_rule(const aci_rule_t* rule, const bind_request_t* request)
{
    return !has_satisfied_any_conditions(rule->exclude, request) && has_satisfied_all_conditions(rule->apply, request);
}

bool has_satisfied_rule(const aci_rule_t* rule, const bind_request_t* request)
{
    return has_satisfied_all_conditions(rule->bind, request);
}
