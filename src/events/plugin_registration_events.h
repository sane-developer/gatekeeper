#ifndef PLUGIN_REGISTRATION_EVENTS_H_
#define PLUGIN_REGISTRATION_EVENTS_H_

#include <dirsrv/slapi-plugin.h>
#include "plugin_registration_status.h"

///
/// @brief Handles plugin registration success.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @return SUCCESSFULLY_REGISTERED.
///
plugin_registration_status_t on_plugin_registration_success(Slapi_PBlock* block);

///
/// @brief Handles plugin registration failure.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @param error Value representing the error that caused the plugin registration failure.
/// @return Respective registration error:
///     a) when plugin failed to get the identity of the plugin,
///     b) when plugin failed to set the description of the plugin,
///     c) when plugin failed to set the version of the utilized LDAP protocol,
///     d) when plugin failed to set the handler of the bind requests,
///     e) when plugin failed to parse the custom ACI rules.
///
plugin_registration_status_t on_plugin_registration_failure(Slapi_PBlock* block, plugin_registration_status_t error);

#endif  // PLUGIN_REGISTRATION_EVENTS_H_
