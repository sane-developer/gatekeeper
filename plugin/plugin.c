#include "aci_rule.h"
#include "aci_rules_parser.h"
#include "bind_request_reporter.h"
#include "logger.h"
#include "plugin.h"

static aci_rules_t* grant_aci_rules;

static aci_rules_t* deny_aci_rules;

plugin_registration_state_t on_registration_success()
{
    write_info_log("%s", "Gatekeeper has been successfully registered.");

    return REGISTRATION_SUCCESS;
}

plugin_registration_state_t on_registration_failure(plugin_registration_state_t error)
{
    switch (error) 
    {
        case FAILED_TO_GET_PLUGIN_IDENTITY:
            write_critical_log("%s", "Directory server failed to retrieve the identity of the plugin.");
            break;
        case FAILED_TO_SET_PLUGIN_DESCRIPTION:
            write_critical_log("%s", "Directory server failed to set the metadata of the plugin.");
            break;
        case FAILED_TO_SET_LDAP_PROTOCOL_VERSION:
            write_critical_log("%s", "Directory server failed to set the version of the LDAP protocol.");
            break;
        case FAILED_TO_SET_BIND_REQUEST_HANDLER:
            write_critical_log("%s", "Directory server failed to set the handler for the bind requests.");
            break;
        case FAILED_TO_SET_CUSTOM_ACI_RULES:
            write_critical_log("%s", "Parser failed to set the custom ACI rules.");
            break;
        default:
            write_critical_log("%s", "Failed due to unknown error.");
            break;
    }

    return error;
}

bind_request_state_t on_granted_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    report_granted_bind_request(block, request);

    dispose_bind_request_parameters(request);

    return REQUEST_GRANTED;
}

bind_request_state_t on_denied_bind_request(Slapi_PBlock* block, bind_request_t* request, bind_request_state_t error)
{
    report_denied_bind_request(block, request, error);

    dispose_bind_request_parameters(request);

    return REQUEST_DENIED;
}

bind_request_state_t on_recieved_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    bind_request_state_t state_after_fetching = fetch_bind_request_parameters(block, &request);

    if (state_after_fetching != PARAMETERS_FETCH_SUCCESS)
    {
        return on_denied_bind_request(block, &request, state_after_fetching);
    }

    bind_request_state_t state_after_deny_rules_evaluation = satisfies_deny_aci_rules(deny_aci_rules, &request);

    if (state_after_deny_rules_evaluation != SATISFIED_DENY_ACI_RULES)
    {
        return on_denied_bind_request(block, &request, state_after_deny_rules_evaluation);
    }

    bind_request_state_t state_after_grant_rules_evaluation = satisfies_grant_aci_rules(grant_aci_rules, &request);

    if (state_after_grant_rules_evaluation != SATISFIED_GRANT_ACI_RULES)
    {
        return on_denied_bind_request(block, &request, state_after_grant_rules_evaluation);
    }

    return on_granted_bind_request(block, &request);
}

int register_plugin(Slapi_PBlock* block)
{
    if (slapi_pblock_get(block, SLAPI_PLUGIN_IDENTITY, plugin_id) != 0)
    {
        return on_registration_failure(FAILED_TO_GET_PLUGIN_IDENTITY);
    }

    if (slapi_pblock_set(block, SLAPI_PLUGIN_DESCRIPTION, &plugin_desc) != 0)
    {
        return on_registration_failure(FAILED_TO_SET_PLUGIN_DESCRIPTION);
    }

    if (slapi_pblock_set(block, SLAPI_PLUGIN_VERSION, SLAPI_PLUGIN_VERSION_03) != 0)
    {
        return on_registration_failure(FAILED_TO_SET_LDAP_PROTOCOL_VERSION);
    }

    if (slapi_pblock_set(block, SLAPI_PLUGIN_PRE_BIND_FN, on_recieved_bind_request) != 0)
    {
        return on_registration_failure(FAILED_TO_SET_BIND_REQUEST_HANDLER);
    }

    if (!set_aci_rules(block, grant_aci_rules, deny_aci_rules))
    {
        return on_registration_failure(FAILED_TO_SET_CUSTOM_ACI_RULES);
    }

    return on_registration_success();
}
