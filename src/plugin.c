#include "bind_request_evaluator.h"
#include "plugin_bootstrapper.h"

static aci_rule_t* plugin_grant_rules;

static aci_rule_t* plugin_deny_rules;

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
    return evaluate_bind_request(block, plugin_grant_rules, plugin_deny_rules);
}

static plugin_bootstrapper_status_t signal_finished_registration(Slapi_PBlock* block)
{
    on_finished_registration((finished_registration_event_args_t) {
        .block = block
    });

    return REGISTERED_PLUGIN;
}

static plugin_bootstrapper_status_t signal_aborted_registration(Slapi_PBlock* block, plugin_bootstrapper_error_t error)
{
    on_aborted_registration((aborted_registration_event_args_t) {
        .block = block,
        .error = error
    });

    return error;
}

plugin_bootstrapper_status_t register_plugin(Slapi_PBlock* block)
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

    return signal_finished_registration(block);
}
