#include "aci_rule_evaluator.h"
#include "bind_request_events.h"
#include "bind_request_provider.h"

static bind_request_status_t grant_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    on_granted_bind_request(block, request);

    dispose_bind_request_parameters(request);

    return REQUEST_GRANTED;
}

static bind_request_status_t deny_bind_request(Slapi_PBlock* block, bind_request_t* request, bind_request_error_t error)
{
    on_denied_bind_request(block, request, error);

    dispose_bind_request_parameters(request);

    return REQUEST_DENIED;
}

static bind_request_status_t satisfies_grant_rules(const aci_rules_t* rules, bind_request_t* request)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        aci_rule_t* rule = rules->items[i];

        if (!has_applied_rule(rule, request))
        {
            continue;
        }

        if (!has_satisfied_rule(rule, request))
        {
            return REQUEST_DENIED;
        }
    }

    return REQUEST_SATISFIED_GRANT_RULES;
}

static bind_request_status_t satisfies_deny_rules(const aci_rules_t* rules, bind_request_t* request)
{
    for (size_t i = 0; i < rules->count; ++i)
    {
        aci_rule_t* rule = rules->items[i];

        if (!has_applied_rule(rule, request))
        {
            continue;
        }

        if (has_satisfied_rule(rule, request))
        {
            return REQUEST_DENIED;
        }
    }

    return REQUEST_SATISFIED_DENY_RULES;
}

bind_request_status_t handle_bind_request(Slapi_PBlock* block, aci_rules_t* grant_rules, aci_rules_t* deny_rules)
{
    bind_request_t request = {0};

    bind_request_status_t status_after_fetching_request_parameters = fetch_bind_request_parameters(block, &request);

    if (status_after_fetching_request_parameters != REQUEST_PARAMETERS_FETCH_SUCCESS)
    {
        return deny_bind_request(block, &request, status_after_fetching_request_parameters);
    }

    bind_request_status_t status_after_deny_rules_evaluation = satisfies_deny_rules(deny_rules, &request);

    if (status_after_deny_rules_evaluation != REQUEST_SATISFIED_DENY_RULES)
    {
        return deny_bind_request(block, &request, status_after_deny_rules_evaluation);
    }

    bind_request_status_t status_after_grant_rules_evaluation = satisfies_grant_rules(grant_rules, &request);

    if (status_after_grant_rules_evaluation != REQUEST_SATISFIED_GRANT_RULES)
    {
        return deny_bind_request(block, &request, status_after_grant_rules_evaluation);
    }

    return grant_bind_request(block, &request);
}
