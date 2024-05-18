#include "bind_request_evaluator.h"
#include "bind_request_resolver.h"
#include "plugin_registration_errors.h"
#include "plugin_registration_handler.h"
#include "plugin_registration_event_dispatcher.h"
#include "plugin_registration_status.h"

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
        return deny_bind_request(&request);
    }

    if (has_triggered_any_deny_rules(block, plugin_deny_rules, &request))
    {
        return deny_bind_request(&request);
    }

    if (has_triggered_any_grant_rules(block, plugin_grant_rules, &request))
    {
        return deny_bind_request(&request);
    }

    return grant_bind_request(&request);
}

static plugin_registration_status_t signal_accepted_registration(Slapi_PBlock* block)
{
    on_accepted_registration((accepted_registration_event_args_t) {
        .block = block
    });

    return REGISTRATION_ACCEPTED;
}

static plugin_registration_status_t signal_aborted_registration(Slapi_PBlock* block, plugin_registration_error_t error)
{
    on_aborted_registration((aborted_registration_event_args_t) {
        .block = block,
        .error = error
    });

    return REGISTRATION_ABORTED;
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

    if (!set_plugin_bind_policy(block, plugin_grant_rules, plugin_deny_rules))
    {
        return signal_aborted_registration(block, FAILED_TO_SET_PLUGIN_BIND_POLICY);
    }

    return signal_accepted_registration(block);
}
