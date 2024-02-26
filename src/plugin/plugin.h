#ifndef GATEKEEPER_PLUGIN_H
#define GATEKEEPER_PLUGIN_H

#include <dirsrv/slapi-plugin.h>
#include "../../sdk/requests/bind_request.h"

///
/// @brief
///
static Slapi_ComponentId* plugin_id;

///
/// @brief
///
static Slapi_PluginDesc plugin_description =
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Plugin which allows to restrict access to the directory server.",
};

///
/// @brief
///
static binding_policy_t* plugin_binding_policy;

///
/// @brief
///
static logging_policy_t* plugin_logging_policy;

///
/// @brief Initializes the resources required to properly run the plugin.
/// @param block The request details sent by directory server.
/// @return 0, when the plugin is successfully initialized; otherwise, 1.
///
int initialize_plugin(Slapi_PBlock* block);

///
/// @brief Evaluates the incoming bind request based on the plugin's binding policy.
/// @param block The request details sent by directory server.
/// @return 0, when the bind request is permitted; otherwise, 1.
///
int evaluate_bind_request(Slapi_PBlock* block);

#endif
