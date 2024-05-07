#include "bind_request_evaluator.h"

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
                if (!satisfies_roles_condition(condition, request->roles))
                {
                    return false;
                }

                break;
            }
            case GROUPS:
            {
                if (!satisfies_groups_condition(condition, request->groups))
                {
                    return false;
                }

                break;
            }
            case ATTRIBUTES:
            {
                if (!satisfies_attributes_condition(condition, request->attributes))
                {
                    return false;
                }

                break;
            }
            case DAY_OF_WEEK:
            {
                if (!satisfies_day_of_week_condition(condition, request->day_of_week))
                {
                    return false;
                }

                break;
            }
            case TIME_OF_DAY:
            {
                if (!satisfies_time_of_day_condition(condition, request->time_of_day))
                {
                    return false;
                }

                break;
            }
        }
    }

    return true;
}

static bool has_excluded(const aci_rule_t* rule, const bind_request_t* request)
{
    return satisfies_rule_conditions(rule->exclude, request);
}

static bool has_applied(const aci_rule_t* rule, const bind_request_t* request)
{
    return satisfies_rule_conditions(rule->apply, request);
}

static bool has_satisfied(const aci_rule_t* rule, const bind_request_t* request)
{
    return satisfies_rule_conditions(rule->bind, request);
}

bind_request_status_t satisfies_grant_rules(const aci_rules_t* rules, bind_request_t* request)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        aci_rule_t* rule = rules->items[i];

        if (has_excluded(rule, request))
        {
            continue;
        }

        if (!has_applied(rule, request))
        {
            continue;
        }

        if (!has_satisfied(rule, request))
        {
            return REQUEST_DENIED;
        }
    }

    return REQUEST_SATISFIED_GRANT_RULES;
}

bind_request_status_t satisfies_deny_rules(const aci_rules_t* rules, bind_request_t* request)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        aci_rule_t* rule = rules->items[i];

        if (has_excluded(rule, request))
        {
            continue;
        }

        if (!has_applied(rule, request))
        {
            continue;
        }

        if (has_satisfied(rule, request))
        {
            return REQUEST_DENIED;
        }
    }

    return REQUEST_SATISFIED_DENY_RULES;
}
