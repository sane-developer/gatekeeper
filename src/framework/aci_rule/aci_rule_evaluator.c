#include "aci_rule_evaluator.h"
#include "aci_rule_operation_provider.h"

static bool has_satisfied_operation(const aci_rule_condition_t* condition, const bind_request_t* request)
{
    return get_operation(condition->parameter, condition->operation)(condition->operands, request);
}

static bool has_satisfied_subcondition(const aci_rule_condition_t** subcondition, const bind_request_t* request)
{
    bool state = true;

    for (const aci_rule_condition_t* subexpression = *subcondition; subexpression->next != NULL; subexpression = subexpression->next)
    {
        state &= has_satisfied_operation(subexpression, request);

        if (!state)
        {
            return false;
        }

        if (subexpression->operator == OR)
        {
            break;
        }
    }

    return state;
}

static bool has_satisfied_condition(const aci_rule_condition_t* condition, const bind_request_t* request)
{
    bool state = false;

    for (const aci_rule_condition_t* expression = condition; expression->next != NULL; expression = expression->next)
    {
        switch (expression->operator)
        {
            case AND:
                state |= has_satisfied_subcondition(&expression, request);
                break;
            case OR:
                state |= has_satisfied_operation(expression, request);
                break;
        }

        if (state)
        {
            return true;
        }
    }

    return state;
}

static bool has_satisfied_any_conditions(const aci_rule_condition_t** conditions, const bind_request_t* request)
{
    for (size_t i = 0; i < MAXIMUM_CONDITIONS_COUNT; ++i)
    {
        if (has_satisfied_condition(conditions[i], request))
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
        if (!has_satisfied_condition(conditions[i], request))
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
