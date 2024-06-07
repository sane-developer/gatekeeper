#include "bind_request.h"

/* Available operations for DN attribute */

static bool dn_matches(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dn_equals(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dn_starts_with(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dn_ends_with(const char* source, const aci_rule_operand_t* operands)
{
    return true;
}

/* Available operations for groups attribute */

static bool groups_all(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool groups_any(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Available operations for IP attribute */

static bool ip_between(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool ip_matches(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return true;
}

static bool ip_equals(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Available operations for DNS attribute */

static bool dns_between(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dns_matches(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dns_equals(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Available operations for time attribute */

static bool time_after(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool time_before(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool time_between(uint32_t source, const aci_rule_operand_t* operands)
{
    return true;
}

/* Available operations for weekday attribute */

static bool weekday_after(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool weekday_before(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool weekday_between(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool weekday_equals(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Resolvers for operations of each supported bind request attribute */

static bool has_satisfied_dn_operation(const char* dn, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case MATCHES:
            return dn_matches(dn, operation->operands);
        case EQUALS:
            return dn_equals(dn, operation->operands);
        case STARTS_WITH:
            return dn_starts_with(dn, operation->operands);
        case ENDS_WITH:
            return dn_ends_with(dn, operation->operands);
        default:
            return false;
    }
}

static bool has_satisfied_groups_operation(const char* groups, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case ALL:
            return groups_all(groups, operation->operands);
        case ANY:
            return groups_any(groups, operation->operands);
        default:
            return false;
    }
}

static bool has_satisfied_ip_operation(const PRNetAddr* ip, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case BETWEEN:
            return ip_between(ip, operation->operands);
        case MATCHES:
            return ip_matches(ip, operation->operands);
        case EQUALS:
            return ip_equals(ip, operation->operands);
        default:
            return false;
    }
}

static bool has_satisfied_dns_operation(const PRNetAddr* dns, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case BETWEEN:
            return dns_between(dns, operation->operands);
        case MATCHES:
            return dns_matches(dns, operation->operands);
        case EQUALS:
            return dns_equals(dns, operation->operands);
        default:
            return false;
    }
}

static bool has_satisfied_time_operation(uint32_t time, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case AFTER:
            return time_after(time, operation->operands);
        case BEFORE:
            return time_before(time, operation->operands);
        case BETWEEN:
            return time_between(time, operation->operands);
        default:
            return false;
    }
}

static bool has_satisfied_weekday_operation(uint32_t weekday, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case AFTER:
            return weekday_after(weekday, operation->operands);
        case BEFORE:
            return weekday_before(weekday, operation->operands);
        case BETWEEN:
            return weekday_between(weekday, operation->operands);
        case EQUALS:
            return weekday_equals(weekday, operation->operands);
        default:
            return false;
    }
}

static bool satisfies_operation_for_attribute(const bind_request_t* request, const aci_rule_operation_t* operation)
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

/* Evaluators for both ACI rule types */

static bool has_satisfied_condition(const bind_request_t* request, const aci_rule_condition_t* condition)
{
    bool is_condition_satisfied = false;

    bool is_subcondition_satisfied = true;

    bool skip_to_next_non_and_operator = false;

    aci_rule_operator_type_t current_operator = NOP;

    aci_rule_operator_type_t next_operator = NOP;

    for (size_t i = 0; i < OPERATIONS_LIMIT; ++i)
    {
        const aci_rule_operation_t* operation = &condition->operations[i];

        current_operator = next_operator;

        next_operator = operation->operator_type;

        if (next_operator == AND)
        {
            is_subcondition_satisfied &= satisfies_operation_for_attribute(request, operation);

            continue;
        }

        if (next_operator == OR)
        {
            switch (current_operator)
            {
                case NOP:
                {
                    is_condition_satisfied |= satisfies_operation_for_attribute(request, operation);

                    break;
                }
                case AND:
                {
                    is_subcondition_satisfied &= satisfies_operation_for_attribute(request, operation);

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
                    return satisfies_operation_for_attribute(request, operation);
                }
                case AND:
                {
                    is_subcondition_satisfied &= satisfies_operation_for_attribute(request, operation);

                    is_condition_satisfied |= is_subcondition_satisfied;

                    break;
                }
                case OR:
                {
                    is_condition_satisfied |= satisfies_operation_for_attribute(request, operation);

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
    for (size_t i = 0; i < CONDITIONS_LIMIT; ++i)
    {
        const aci_rule_condition_t* condition = &rule->exclude[i];

        if (has_satisfied_condition(request, condition))
        {
            return false;
        }

        if (condition->is_last)
        {
            break;
        }
    }

    for (size_t i = 0; i < CONDITIONS_LIMIT; ++i)
    {
        const aci_rule_condition_t* condition = &rule->apply[i];

        if (!has_satisfied_condition(request, condition))
        {
            return false;
        }

        if (condition->is_last)
        {
            break;
        }
    }

    return true;
}

static bool has_satisfied_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rule_t* rule)
{
    for (size_t i = 0; i < CONDITIONS_LIMIT; ++i)
    {
        const aci_rule_condition_t* condition = &rule->satisfy[i];

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

        if (condition->is_last)
        {
            break;
        }
    }

    return true;
}

static bool has_triggered_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rule_t* rule)
{
    for (size_t i = 0; i < CONDITIONS_LIMIT; ++i)
    {
        const aci_rule_condition_t* condition = &rule->satisfy[i];

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

        if (condition->is_last)
        {
            break;
        }
    }

    return false;
}

bool has_triggered_any_grant_rule(Slapi_PBlock* block, const bind_request_t* request, const bind_policy_t* policy)
{
    for (size_t i = 0; i < RULES_LIMIT; ++i)
    {
        const aci_rule_t* rule = &policy->deny_rules[i];

        if (has_applied_rule(request, rule) && !has_satisfied_rule(block, request, rule))
        {
            return true;
        }

        if (rule->is_last)
        {
            break;
        }
    }

    on_bind_request_granted((on_bind_request_granted_event_args_t) {
        .block = block,
        .request = request
    });

    return false;
}

bool has_triggered_any_deny_rule(Slapi_PBlock* block, const bind_request_t* request, const bind_policy_t* policy)
{
    for (size_t i = 0; i < RULES_LIMIT; ++i)
    {
        const aci_rule_t* rule = &policy->deny_rules[i];

        if (has_applied_rule(request, rule) && has_triggered_rule(block, request, rule))
        {
            return true;
        }

        if (rule->is_last)
        {
            break;
        }
    }

    return false;
}
