#include "aci_rule_evaluator.h"
#include "aci_rule_conditions.h"

static bool satisfies_rule_conditions(const aci_rule_conditions_t* conditions, const bind_request_t* request)
{
    for (size_t i = 0; i < conditions->count; ++i)
    {
        aci_rule_condition_t* condition = conditions->items[i];

        switch (condition->parameter)
        {
            case DN:
            {
                if (!satisfies_dn_condition(condition, request->dn))
                {
                    return false;
                }

                break;
            }
            case IP:
            {
                if (!satisfies_ip_condition(condition, request->ip))
                {
                    return false;
                }

                break;
            }
            case DNS:
            {
                if (!satisfies_dns_condition(condition, request->dns))
                {
                    return false;
                }

                break;
            }
            case ROLES:
            {
                const char** roles = (const char**) request->roles;

                if (!satisfies_roles_condition(condition, roles))
                {
                    return false;
                }

                break;
            }
            case GROUPS:
            {
                const char** groups = (const char**) request->groups;

                if (!satisfies_groups_condition(condition, groups))
                {
                    return false;
                }

                break;
            }
            case ATTRIBUTES:
            {
                const char** attributes = (const char**) request->attributes;

                if (!satisfies_attributes_condition(condition, attributes))
                {
                    return false;
                }

                break;
            }
            case DAY_OF_WEEK:
            {
                if (!satisfies_day_of_week_condition(condition, &request->datetime))
                {
                    return false;
                }

                break;
            }
            case TIME_OF_DAY:
            {
                if (!satisfies_time_of_day_condition(condition, &request->datetime))
                {
                    return false;
                }

                break;
            }
        }
    }

    return true;
}

bind_request_status_t evaluate_against_grant_rules(const aci_rules_t* rules, bind_request_t* request)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        aci_rule_t* rule = rules->items[i];

        if (satisfies_rule_conditions(rule->exclude, request))
        {
            continue;
        }

        if (!satisfies_rule_conditions(rule->apply, request))
        {
            continue;
        }

        if (!satisfies_rule_conditions(rule->bind, request))
        {
            return REQUEST_DENIED;
        }
    }

    return REQUEST_SATISFIED_GRANT_RULES;
}

bind_request_status_t evaluate_against_deny_rules(const aci_rules_t* rules, bind_request_t* request)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        aci_rule_t* rule = rules->items[i];

        if (satisfies_rule_conditions(rule->exclude, request))
        {
            continue;
        }

        if (!satisfies_rule_conditions(rule->apply, request))
        {
            continue;
        }

        if (satisfies_rule_conditions(rule->bind, request))
        {
            return REQUEST_DENIED;
        }
    }

    return REQUEST_SATISFIED_DENY_RULES;
}
