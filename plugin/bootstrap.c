#include "plugin.h"

bind_policy_t plugin_bind_policy = {0};

Slapi_ComponentId* plugin_identity = NULL;

Slapi_PluginDesc plugin_description = (Slapi_PluginDesc)
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Evaluates LDAP bind request against extended ACI policy."
};

plugin_registration_status_t handle_plugin_registration(Slapi_PBlock* block)
{
    if (!has_resolved_plugin_identity(block))
    {
        return abort_plugin_registration(block, PLUGIN_IDENTITY_UNRESOLVED);
    }

    if (!has_resolved_plugin_description(block))
    {
        return abort_plugin_registration(block, PLUGIN_DESCRIPTION_UNRESOLVED);
    }

    if (!has_resolved_plugin_ldap_protocol_version(block))
    {
        return abort_plugin_registration(block, PLUGIN_LDAP_PROTOCOL_VERSION_UNRESOLVED);
    }

    if (!has_resolved_plugin_bind_request_handler(block))
    {
        return abort_plugin_registration(block, PLUGIN_BIND_REQUEST_HANDLER_UNRESOLVED);
    }

    if (!has_resolved_bind_policy(block, &plugin_bind_policy))
    {
        return abort_plugin_registration(block, PLUGIN_BIND_POLICY_UNRESOLVED);
    }

    return finish_plugin_registration(block);
}
