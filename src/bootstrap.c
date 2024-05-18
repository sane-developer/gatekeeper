#include "bind_request_evaluator.h"
#include "bind_request_resolver.h"
#include "plugin_registration_handler.h"

static aci_rule_linked_list_t* grant_rules;

static aci_rule_linked_list_t* deny_rules;

static Slapi_ComponentId* plugin_identity;

static Slapi_PluginDesc plugin_description =
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Evaluates bind requests against user-defined ACI rules."
};

static bind_request_status_t handle_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    aci_rule_identity_t rule_identity = {0};

    if (!resolve_bind_request_parameters(block, &request))
    {
        return signal_denied_bind_request(block, &request, &rule_identity);
    }

    if (has_triggered_any_deny_rules(&request, deny_rules, &rule_identity))
    {
        return signal_denied_bind_request(block, &request, &rule_identity);
    }

    if (has_triggered_any_grant_rules(&request, grant_rules, &rule_identity))
    {
        return signal_denied_bind_request(block, &request, &rule_identity);
    }

    return signal_granted_bind_request(block, &request);
}

plugin_registration_status_t register_plugin(Slapi_PBlock* block)
{
    if (!get_plugin_identity(block, plugin_identity))
    {
        return signal_aborted_registration(block, FAILED_TO_GET_PLUGIN_IDENTITY);
    }

    if (!set_plugin_description(block, &plugin_description))
    {
        return signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_DESCRIPTION);
    }

    if (!set_plugin_ldap_protocol_version(block))
    {
        return signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_LDAP_PROTOCOL_VERSION);
    }

    if (!set_plugin_bind_request_handler(block, handle_bind_request))
    {
        return signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_BIND_REQUEST_HANDLER);
    }

    if (!set_plugin_bind_policy(block, grant_rules, deny_rules))
    {
        return signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_BIND_POLICY);
    }

    return signal_accepted_registration(block);
}
