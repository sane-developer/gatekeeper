#include "aci_rule_evaluator.h"
#include "aci_rules_parser.h"
#include "bind_request_events.h"
#include "plugin_registration_events.h"
#include "plugin.h"

static int get_plugin_identity(Slapi_PBlock* block)
{
    return slapi_pblock_get(block, SLAPI_PLUGIN_IDENTITY, plugin_identity) == 0;
}

static int set_plugin_api_version(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_VERSION, SLAPI_PLUGIN_VERSION_03) == 0;
}

static int set_plugin_description(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_DESCRIPTION, &plugin_description) == 0;
}

static int set_plugin_bind_request_handler(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_PRE_BIND_FN, handle_bind_request) == 0;
}

plugin_registration_status_t register_gatekeeper(Slapi_PBlock* block)
{
    if (!get_plugin_identity(block))
    {
        return on_plugin_registration_failure(block, FAILED_TO_GET_PLUGIN_IDENTITY);
    }

    if (!set_plugin_api_version(block))
    {
        return on_plugin_registration_failure(block, FAILED_TO_SET_PLUGIN_API_VERSION);
    }
    
    if (!set_plugin_description(block))
    {
        return on_plugin_registration_failure(block, FAILED_TO_SET_PLUGIN_DESCRIPTION);
    }

    if (!set_plugin_bind_request_handler(block))
    {
        return on_plugin_registration_failure(block, FAILED_TO_SET_PLUGIN_BIND_REQUEST_HANDLER);
    }

    if (!parse_custom_aci_rules(block, grant_aci_rules, deny_aci_rules))
    {
        return on_plugin_registration_failure(block, FAILED_TO_PARSE_CUSTOM_ACI_RULES);
    }

    return on_plugin_registration_success(block);
}

bind_request_status_t handle_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = 
    {
        .client = {0},
        .connection = {0}
    };

    bind_request_status_t status_after_fetching_client_parameters = fetch_ldap_client_parameters(block, &request.client); 
    
    if (status_after_fetching_client_parameters != FETCHED_CLIENT_PARAMETERS)
    {
        return on_denied_bind_request(block, &request, status_after_fetching_client_parameters);
    }

    bind_request_status_t status_after_fetching_connection_parameters = fetch_ldap_connection_parameters(block, &request.connection);

    if (status_after_fetching_connection_parameters != FETCHED_CONNECTION_PARAMETERS)
    {
        return on_denied_bind_request(block, &request, status_after_fetching_connection_parameters);
    }

    bind_request_status_t status_after_evaluating_deny_aci_rules = evaluate_deny_aci_rules(deny_aci_rules, &request);

    if (status_after_evaluating_deny_aci_rules != SATISFIED_DENY_ACI_RULES)
    {
        return on_denied_bind_request(block, &request, status_after_evaluating_deny_aci_rules);
    }

    bind_request_status_t status_after_evaluating_grant_aci_rules = evaluate_grant_aci_rules(grant_aci_rules, &request);

    if (status_after_evaluating_grant_aci_rules != SATISFIED_GRANT_ACI_RULES)
    {
        return on_denied_bind_request(block, &request, status_after_evaluating_grant_aci_rules);
    }

    return on_granted_bind_request(block, &request);
}
