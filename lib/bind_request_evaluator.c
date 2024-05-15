#include <dirsrv/slapi-plugin.h>
#include "bind_request_evaluator.h"
#include "aci_rule_operation_provider.h"

static bool has_satisfied_operation(struct aci_rule_expression_t* expression, bind_request_t* request)
{
    return get_operation_for_operand(expression->operand, expression->operation)(expression->values, request);
}

static bool has_satisfied_subcondition(struct aci_rule_expression_t** subexpression, bind_request_t* request)
{
    for (struct aci_rule_expression_t* head = *subexpression; head != NULL; head = head->next)
    {
        if (!has_satisfied_operation(head, request))
        {
            return false;
        }
    }

    return true;
}

static bool has_satisfied_condition(struct aci_rule_expression_t* expression, bind_request_t* request)
{
    for (struct aci_rule_expression_t* head = expression; head != NULL; head = head->next)
    {
        switch (head->operator)
        {
            case AND:
            {
                if (has_satisfied_subcondition(&head, request))
                {
                    return true;
                }
            }
            case OR:
            {
                if (has_satisfied_operation(head, request))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

static bool has_satisfied_all_conditions(struct aci_rule_expression_t** expressions, bind_request_t* request)
{
    for (size_t i = 0; i < MAX_EXPRESSIONS_COUNT; ++i)
    {
        struct aci_rule_expression_t* expression = expressions[i];

        if (!has_satisfied_condition(expression, request))
        {
            return false;
        }
    }

    return true;
}

static bool has_satisfied_any_conditions(struct aci_rule_expression_t** expressions, bind_request_t* request)
{
    for (size_t i = 0; i < MAX_EXPRESSIONS_COUNT; ++i)
    {
        struct aci_rule_expression_t* expression = expressions[i];

        if (has_satisfied_condition(expression, request))
        {
            return true;
        }
    }

    return false;
}

static bool has_applied_rule(struct aci_rule_t* rule, bind_request_t* request)
{
    return !has_satisfied_any_conditions(rule->exclude, request) && has_satisfied_all_conditions(rule->apply, request);
}

static bool has_satisfied_rule(struct aci_rule_t* rule, bind_request_t* request)
{
    return has_satisfied_all_conditions(rule->bind, request);
}

bool has_satisfied_deny_rules(struct aci_rule_t* rules, bind_request_t* request)
{
    for (struct aci_rule_t* head = rules; head != NULL; head = head->next)
    {
        if (!has_applied_rule(head, request))
        {
            continue;
        }

        if (has_satisfied_rule(head, request))
        {
            request->reason = slapi_ch_strdup(head->label);

            request->status = FAILED_TO_SATISFY_DENY_RULES;

            return false;
        }
    }

    return true;
}

bool has_satisfied_grant_rules(struct aci_rule_t* rules, bind_request_t* request)
{
    for (struct aci_rule_t* head = rules; head != NULL; head = head->next)
    {
        if (!has_applied_rule(head, request))
        {
            continue;
        }

        if (!has_satisfied_rule(head, request))
        {
            request->reason = slapi_ch_strdup(head->label);

            request->status = FAILED_TO_SATISFY_GRANT_RULES;

            return false;
        }
    }

    return true;
}
