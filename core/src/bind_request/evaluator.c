#include "bind_request.h"

static bool has_satisfied_operation_for_attribute(const bind_request_t* request, const aci_rule_operation_t* operation)
{
    switch (operation->operand_type)
    {
        case DN:
            return has_satisfied_dn_operation(request->dn, operation);
        case GROUPS:
            return has_satisfied_groups_operation(request->groups, operation);
        case IP:
            return has_satisfied_ip_operation(request->ip, operation);
        case DNS:
            return has_satisfied_dns_operation(request->dns, operation);
        case TIME:
            return has_satisfied_time_operation(request->time, operation);
        case WEEKDAY:
            return has_satisfied_weekday_operation(request->weekday, operation);
        default:
            return false;
    }
}

static bool has_satisfied_condition(const bind_request_t* request, const aci_rule_condition_t* condition)
{
    bool is_condition_satisfied = false;

    bool is_subcondition_satisfied = true;

    aci_rule_operator_type_t current_operator = NOP;

    aci_rule_operator_type_t next_operator = NOP;

    for (size_t i = 0; i < condition->operations.count; ++i)
    {
        const aci_rule_operation_t* operation = &condition->operations.items[i];

        current_operator = next_operator;

        next_operator = operation->operator_type;

        if (next_operator == AND)
        {
            is_subcondition_satisfied &= has_satisfied_operation_for_attribute(request, operation);

            continue;
        }

        if (next_operator == OR)
        {
            switch (current_operator)
            {
                case NOP:
                {
                    is_condition_satisfied |= has_satisfied_operation_for_attribute(request, operation);

                    break;
                }
                case AND:
                {
                    is_subcondition_satisfied &= has_satisfied_operation_for_attribute(request, operation);

                    is_condition_satisfied |= is_subcondition_satisfied;

                    is_subcondition_satisfied = true;

                    break;
                }
                case OR:
                {
                    is_condition_satisfied |= is_subcondition_satisfied;

                    break;
                }
            }

            continue;
        }

        if (next_operator == NOP)
        {
            switch (current_operator)
            {
                case NOP:
                {
                    return has_satisfied_operation_for_attribute(request, operation);
                }
                case AND:
                {
                    is_subcondition_satisfied &= has_satisfied_operation_for_attribute(request, operation);

                    is_condition_satisfied |= is_subcondition_satisfied;

                    break;
                }
                case OR:
                {
                    is_condition_satisfied |= has_satisfied_operation_for_attribute(request, operation);

                    break;
                }
            }

            break;
        }
    }

    return is_condition_satisfied;
}

static bool has_applied_rule(const bind_request_t* request, const aci_rule_t* rule)
{
    for (size_t i = 0; i < rule->exclude.count; ++i)
    {
        const aci_rule_condition_t* condition = &rule->exclude.items[i];

        if (has_satisfied_condition(request, condition))
        {
            return false;
        }
    }

    for (size_t i = 0; i < rule->apply.count; ++i)
    {
        const aci_rule_condition_t* condition = &rule->apply.items[i];

        if (!has_satisfied_condition(request, condition))
        {
            return false;
        }
    }

    return true;
}

static bool has_satisfied_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rule_t* rule)
{
    for (size_t i = 0; i < rule->trigger.count; ++i)
    {
        const aci_rule_condition_t* condition = &rule->trigger.items[i];

        if (!has_satisfied_condition(request, condition))
        {
            on_bind_request_denied((on_bind_request_denied_event_args_t) {
                .block = block,
                .request = request,
                .violated_rule_label = &rule->label[0],
                .violated_condition_label = &condition->label[0]
            });

            return false;
        }
    }

    return true;
}

static bool has_triggered_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rule_t* rule)
{
    for (size_t i = 0; i < rule->trigger.count; ++i)
    {
        const aci_rule_condition_t* condition = &rule->trigger.items[i];

        if (has_satisfied_condition(request, condition))
        {
            on_bind_request_denied((on_bind_request_denied_event_args_t) {
                .block = block,
                .request = request,
                .violated_rule_label = &rule->label[0],
                .violated_condition_label = &condition->label[0]
            });

            return true;
        }
    }

    return false;
}

bool has_triggered_any_special_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rules_t* rules)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        const aci_rule_t* rule = &rules->items[i];

        if (has_applied_rule(request, rule) && has_satisfied_rule(block, request, rule))
        {
            on_bind_request_granted((on_bind_request_granted_event_args_t) {
                .block = block,
                .request = request
            });

            return true;
        }
    }

    return false;
}

bool has_triggered_any_grant_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rules_t* rules)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        const aci_rule_t* rule = &rules->items[i];

        if (has_applied_rule(request, rule) && !has_satisfied_rule(block, request, rule))
        {
            return true;
        }
    }

    on_bind_request_granted((on_bind_request_granted_event_args_t) {
        .block = block,
        .request = request
    });

    return false;
}

bool has_triggered_any_deny_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rules_t* rules)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        const aci_rule_t* rule = &rules->items[i];

        if (has_applied_rule(request, rule) && has_triggered_rule(block, request, rule))
        {
            return true;
        }
    }

    return false;
}
