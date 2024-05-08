#include "aci_rule_evaluator.h"
#include "aci_rule_operation_provider.h"

typedef struct
{
    bool or_state;

    bool and_state;

    bool skip_till_next_or;

    aci_rule_operator_t operator;
}
aci_rule_evaluator_state_t;

static bool handle_or_operator(aci_rule_evaluator_state_t* state, aci_rule_expression_t* head, bind_request_t* request)
{
    if (state->and_state)
    {
        return true; // The output will always be 1 at this point.
    }

    state->and_state |= operation(head->operands, request);

    state->or_state &= state.and_state;

    state->and_state = true; // The substate must be reset in case the next operation is AND;

    return false;
}

static bool handle_and_operator(aci_rule_evaluator_state_t* state, aci_rule_expression_t* head, bind_request_t* request)
{
    if (!state->and_state)
    {
        state->skip_till_next_or = true;

        return false;
    }

    state->and_state &= operation(head->operands, request);
}

static bool has_satisfied_condition(const aci_rule_condition_t* condition, const bind_request_t* request)
{
    const struct aci_rule_expression_t* head;

    aci_rule_evaluator_state_t state =
    {
        .or_state = 1,
        .and_state = 1,
        .skip_till_next_or = 0,
        .operator = AND
    };

    while (head)
    {
        aci_rule_operation operation = get_operation(head->parameter, state.head->operation);

        switch (state.operator)
        {
            case AND:
                handle_and_operator();
                break;
            case OR:
                handle_or_operator();
                break;
            case TERMINATOR:
                return state.or_state & state.and_state; // The end of the evaluation.
        }

        state.operator = head->operator;

        head = head->next;
    }

    return state.or_state;
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
