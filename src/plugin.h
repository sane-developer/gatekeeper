#ifndef PLUGIN_H
#define PLUGIN_H

#include "bind_policy.h"
#include <dirsrv/slapi-plugin.h>
#include "plugin_registration_status.h"

///
/// @brief The bind policy of the plugin.
///
static bind_policy_t policy = {0};

///
/// @brief The identity of the plugin.
///
static Slapi_ComponentId* identity;

///
/// @brief The metadata of the plugin.
///
static Slapi_PluginDesc description =
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Evaluates bind requests against user-defined ACI rules."
};

///
/// @brief
/// @param
/// @return
/// @remarks
///
plugin_registration_status_t register_plugin(Slapi_PBlock* block);

#endif  // PLUGIN_H
