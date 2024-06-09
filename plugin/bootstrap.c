#include "plugin_bootstrap.h"

bind_policy_t plugin_bind_policy = {0};

Slapi_ComponentId* plugin_component_identity = NULL;

Slapi_PluginDesc plugin_component_description = (Slapi_PluginDesc)
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Evaluates LDAP bind request against extended ACI policy."
};

bind_request_status_t handle_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    if (!has_resolved_bind_request(block, &request))
    {
        return deny_bind_request(&request);
    }

    if (has_triggered_any_special_rule(block, &request, &plugin_bind_policy.special))
    {
        return grant_bind_request(&request);
    }

    if (has_triggered_any_deny_rule(block, &request, &plugin_bind_policy.deny))
    {
        return deny_bind_request(&request);
    }

    if (has_triggered_any_grant_rule(block, &request, &plugin_bind_policy.grant))
    {
        return deny_bind_request(&request);
    }

    return grant_bind_request(&request);
}

plugin_registration_status_t handle_plugin_registration(Slapi_PBlock* block)
{
    if (!has_resolved_plugin_identity(block, plugin_component_identity))
    {
        return abort_plugin_registration(block, PLUGIN_IDENTITY_UNRESOLVED);
    }

    if (!has_resolved_plugin_description(block, &plugin_component_description))
    {
        return abort_plugin_registration(block, PLUGIN_DESCRIPTION_UNRESOLVED);
    }

    if (!has_resolved_plugin_ldap_protocol_version(block))
    {
        return abort_plugin_registration(block, PLUGIN_LDAP_PROTOCOL_VERSION_UNRESOLVED);
    }

    if (!has_resolved_plugin_bind_request_handler(block, handle_bind_request))
    {
        return abort_plugin_registration(block, PLUGIN_BIND_REQUEST_HANDLER_UNRESOLVED);
    }

    if (!has_resolved_plugin_bind_policy(block, &plugin_bind_policy))
    {
        return abort_plugin_registration(block, PLUGIN_BIND_POLICY_UNRESOLVED);
    }

    return finish_plugin_registration(block);
}
