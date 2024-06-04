#include "plugin.h"

static bind_policy_t plugin_policy = {0};

static Slapi_ComponentId* plugin_identity = NULL;

static Slapi_PluginDesc plugin_description = (Slapi_PluginDesc)
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Evaluates LDAP bind request against extended ACI policy."
};

static bool setup_plugin_identity(Slapi_PBlock* block)
{
    return slapi_pblock_get(block, SLAPI_PLUGIN_IDENTITY, plugin_identity) == 0;
}

static bool setup_plugin_description(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_DESCRIPTION, &plugin_description) == 0;
}

static bool setup_plugin_ldap_protocol_version(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_VERSION, SLAPI_PLUGIN_VERSION_03) == 0;
}

static bool setup_plugin_bind_request_handler(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_PRE_BIND_FN, handle_bind_request) == 0;
}

static plugin_registration_status_t signal_plugin_registration_success(on_plugin_registered_event_args_t args)
{
    on_plugin_registered(&args);

    return PLUGIN_REGISTERED;
}

static plugin_registration_status_t signal_plugin_registration_failure(on_plugin_unregistered_event_args_t args)
{
    on_plugin_unregistered(&args);

    return PLUGIN_UNREGISTERED;
}

plugin_registration_status_t handle_plugin_registration(Slapi_PBlock* block)
{
    if (!setup_plugin_identity(block))
    {
        return signal_plugin_registration_failure((on_plugin_unregistered_event_args_t) {
            .block = block,
            .error = PLUGIN_IDENTITY_SETUP_FAILURE
        });
    }

    if (!setup_plugin_description(block))
    {
        return signal_plugin_registration_failure((on_plugin_unregistered_event_args_t) {
            .block = block,
            .error = PLUGIN_DESCRIPTION_SETUP_FAILURE
        });
    }

    if (!setup_plugin_ldap_protocol_version(block))
    {
        return signal_plugin_registration_failure((on_plugin_unregistered_event_args_t) {
            .block = block,
            .error = PLUGIN_LDAP_PROTOCOL_VERSION_SETUP_FAILURE
        });
    }

    if (!setup_plugin_bind_request_handler(block))
    {
        return signal_plugin_registration_failure((on_plugin_unregistered_event_args_t) {
            .block = block,
            .error = PLUGIN_BIND_REQUEST_HANDLER_SETUP_FAILURE
        });
    }

    if (!setup_bind_policy(block, &plugin_policy))
    {
        return signal_plugin_registration_failure((on_plugin_unregistered_event_args_t) {
            .block = block,
            .error = PLUGIN_BIND_POLICY_SETUP_FAILURE
        });
    }

    return signal_plugin_registration_success((on_plugin_registered_event_args_t) {
        .block = block
    });
}

static bind_request_status_t signal_granted_bind_request(on_bind_request_granted_event_args_t args)
{
    on_bind_request_granted(&args);

    dispose_bind_request(args.request);

    return REQUEST_GRANTED;
}

static bind_request_status_t signal_denied_bind_request(on_bind_request_denied_event_args_t args)
{
    on_bind_request_denied(&args);

    dispose_bind_request(args.request);

    return REQUEST_DENIED;
}

static bind_request_status_t signal_unresolved_bind_request(on_bind_request_unresolved_event_args_t args)
{
    on_bind_request_unresolved(&args);

    dispose_bind_request(args.request);

    return REQUEST_DENIED;
}

bind_request_status_t handle_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    bind_request_status_t status = resolve_bind_request(block, &request);

    if (status != REQUEST_RESOLVED)
    {
        return signal_unresolved_bind_request((on_bind_request_unresolved_event_args_t) {
            .block = block,
            .request = &request,
            .error = status
        });
    }

    char* rule_label;

    char* condition_label;

    if (!satisfies_deny_type_rules(&request, &plugin_policy, rule_label, condition_label))
    {
        return signal_denied_bind_request((on_bind_request_denied_event_args_t) {
            .block = block,
            .request = &request,
            .violated_rule_label = rule_label,
            .violated_condition_label = condition_label
        });
    }

    if (!satisfies_grant_type_rules(&request, &plugin_policy, rule_label, condition_label))
    {
        return signal_denied_bind_request((on_bind_request_denied_event_args_t) {
            .block = block,
            .request = &request,
            .violated_rule_label = rule_label,
            .violated_condition_label = condition_label
        });
    }

    return signal_granted_bind_request((on_bind_request_granted_event_args_t) {
        .block = block,
        .request = &request
    });
}
