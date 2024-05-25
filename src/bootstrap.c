#include "bind_request_event_dispatcher.h"
#include "bind_request_handler.h"
#include "plugin_registration_event_dispatcher.h"
#include "plugin_registration_handler.h"

static aci_rule_linked_list_t* plugin_grant_rules;

static aci_rule_linked_list_t* plugin_deny_rules;

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

    if (!resolve_bind_request_parameters(block, &request))
    {
        signal_denied_bind_request(block, &request);

        return REQUEST_DENIED;
    }

    if (!evaluate_against_deny_rules(block, plugin_deny_rules, &request))
    {
        signal_denied_bind_request(block, &request);

        return REQUEST_DENIED;
    }

    if (!evaluate_against_grant_rules(block, plugin_grant_rules, &request))
    {
        signal_denied_bind_request(block, &request);

        return REQUEST_DENIED;
    }

    signal_granted_bind_request(block, &request);

    return REQUEST_GRANTED;
}

plugin_registration_status_t register_plugin(Slapi_PBlock* block)
{
    if (!get_plugin_identity(block, plugin_identity))
    {
        signal_aborted_registration(block, FAILED_TO_GET_PLUGIN_IDENTITY);

        return REGISTRATION_ABORTED;
    }

    if (!set_plugin_description(block, &plugin_description))
    {
        signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_DESCRIPTION);

        return REGISTRATION_ABORTED;
    }

    if (!set_plugin_ldap_protocol_version(block))
    {
        signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_LDAP_PROTOCOL_VERSION);

        return REGISTRATION_ABORTED;
    }

    if (!set_plugin_bind_request_handler(block, handle_bind_request))
    {
        signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_BIND_REQUEST_HANDLER);

        return REGISTRATION_ABORTED;
    }

    if (!set_plugin_bind_policy(block, plugin_grant_rules, plugin_deny_rules))
    {
        signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_BIND_POLICY);

        return REGISTRATION_ABORTED;
    }

    signal_accepted_registration(block);

    return REGISTRATION_ACCEPTED;
}
