#include "bind_request_handler.h"
#include "plugin_registrar.h"
#include "plugin_registrar_actions.h"
#include "plugin_registrar_status.h"

///
/// @brief The user-defined ACI rules of grant type.
///
static aci_rules_t* grant_rules;

///
/// @brief The user-defined ACI rules of deny type.
///
static aci_rules_t* deny_rules;

///
/// @brief The identity of the plugin.
///
static Slapi_ComponentId* plugin_identity;

///
/// @brief The metadata of the plugin.
///
static Slapi_PluginDesc plugin_description =
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Evaluates bind requests against user-defined ACI rules."
};

///
/// @brief
///
static bind_request_status_t on_recieved_bind_request(Slapi_PBlock* block)
{
    return handle_bind_request(block, grant_rules, deny_rules);
}

///
/// @brief Initializes the plugin within 389 directory server environment.
/// @remark In case the registration fails; directory server will not launch.
/// @remark This is the starting point of the entire application.
///
plugin_registrar_status_t initialize_gatekeeper(Slapi_PBlock* block)
{
    if (!get_plugin_identity(block, plugin_identity))
    {
        return cancel_registration(block, FAILED_TO_GET_PLUGIN_IDENTITY);
    }

    if (!set_plugin_description(block, &plugin_description))
    {
        return cancel_registration(block, FAILED_TO_SET_PLUGIN_DESCRIPTION);
    }

    if (!set_plugin_ldap_protocol_version(block))
    {
        return cancel_registration(block, FAILED_TO_SET_PLUGIN_LDAP_PROTOCOL_VERSION);
    }

    if (!set_plugin_bind_request_handler(block, on_recieved_bind_request))
    {
        return cancel_registration(block, FAILED_TO_SET_PLUGIN_BIND_REQUEST_HANDLER);
    }

    if (!set_plugin_aci_rules(block, grant_rules, deny_rules))
    {
        return cancel_registration(block, FAILED_TO_SET_PLUGIN_CUSTOM_ACI_RULES);
    }

    return register_plugin(block);
}
