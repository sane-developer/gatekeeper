#include "plugin_registration_handler.h"

bool get_plugin_identity(Slapi_PBlock* block, Slapi_ComponentId* identity)
{
    return slapi_pblock_get(block, SLAPI_PLUGIN_IDENTITY, identity) == 0;
}

bool set_plugin_description(Slapi_PBlock* block, Slapi_PluginDesc* description)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_DESCRIPTION, description) == 0;
}

bool set_plugin_ldap_protocol_version(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_VERSION, SLAPI_PLUGIN_VERSION_03) == 0;
}

bool set_plugin_bind_request_handler(Slapi_PBlock* block, bind_request_handler_t handler)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_PRE_BIND_FN, handler) == 0;
}
