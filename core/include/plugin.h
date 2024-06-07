#ifndef PLUGIN_H
#define PLUGIN_H

#include "bind_request.h"

///
/// @brief
///
extern bind_policy_t plugin_bind_policy;

///
/// @brief
///
extern Slapi_ComponentId* plugin_identity;

///
/// @brief
///
extern Slapi_PluginDesc plugin_description;

///
/// @brief
///
typedef enum
{
    PLUGIN_REGISTERED = 0,

    PLUGIN_UNREGISTERED = 1,

    PLUGIN_IDENTITY_UNRESOLVED,

    PLUGIN_DESCRIPTION_UNRESOLVED,

    PLUGIN_LDAP_PROTOCOL_VERSION_UNRESOLVED,

    PLUGIN_BIND_REQUEST_HANDLER_UNRESOLVED,

    PLUGIN_BIND_POLICY_UNRESOLVED
}
plugin_registration_status_t;

///
/// @brief
///
typedef struct
{
    Slapi_PBlock* block;
}
on_plugin_registration_finished_event_args_t;

///
/// @brief
///
typedef struct
{
    Slapi_PBlock* block;

    plugin_registration_status_t error;
}
on_plugin_registration_aborted_event_args_t;

///
/// @brief
/// @param args
///
void on_plugin_registration_finished(on_plugin_registration_finished_event_args_t args);

///
/// @brief
/// @param args
///
void on_plugin_registration_aborted(on_plugin_registration_aborted_event_args_t args);

///
/// @brief
/// @param block
/// @return
///
bool has_resolved_plugin_identity(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @return
///
bool has_resolved_plugin_description(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @return
///
bool has_resolved_plugin_ldap_protocol_version(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @return
///
bool has_resolved_plugin_bind_request_handler(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @return
///
plugin_registration_status_t finish_plugin_registration(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @param error
/// @return
///
plugin_registration_status_t abort_plugin_registration(Slapi_PBlock* block, plugin_registration_status_t error);

///
/// @brief
/// @param block
/// @return
///
plugin_registration_status_t handle_plugin_registration(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @return
///
bind_request_status_t handle_bind_request(Slapi_PBlock* block);

#endif  // PLUGIN_H
