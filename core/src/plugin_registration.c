#include "plugin_registration.h"

bool has_resolved_plugin_identity(Slapi_PBlock* block, Slapi_ComponentId* identity)
{
    return slapi_pblock_get(block, SLAPI_PLUGIN_IDENTITY, identity) == 0;
}

bool has_resolved_plugin_description(Slapi_PBlock* block, Slapi_PluginDesc* description)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_DESCRIPTION, description) == 0;
}

bool has_resolved_plugin_ldap_protocol_version(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_VERSION, SLAPI_PLUGIN_VERSION_03) == 0;
}

bool has_resolved_plugin_bind_request_handler(Slapi_PBlock* block, plugin_bind_request_handler_t handler)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_PRE_BIND_FN, handler) == 0;
}

plugin_registration_status_t finish_plugin_registration(Slapi_PBlock* block)
{
    on_plugin_registration_finished((on_plugin_registration_finished_event_args_t) {
        .block = block
    });

    return PLUGIN_REGISTERED;
}

plugin_registration_status_t abort_plugin_registration(Slapi_PBlock* block, plugin_registration_status_t error)
{
    on_plugin_registration_aborted((on_plugin_registration_aborted_event_args_t) {
        .block = block,
        .error = error
    });

    return PLUGIN_UNREGISTERED;
}
