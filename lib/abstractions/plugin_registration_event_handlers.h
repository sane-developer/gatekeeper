#ifndef PLUGIN_REGISTRATION_EVENT_HANDLERS_H
#define PLUGIN_REGISTRATION_EVENT_HANDLERS_H

#include <dirsrv/slapi-plugin.h>
#include "plugin_registration_status.h"

///
/// @brief
/// @param block
///
void on_plugin_registration_success(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @param error
///
void on_plugin_registration_failure(Slapi_PBlock* block, plugin_registration_error_t error);

#endif  // PLUGIN_REGISTRATION_EVENT_HANDLERS_H
