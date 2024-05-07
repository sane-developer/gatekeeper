#ifndef PLUGIN_REGISTRAR_EVENTS_H
#define PLUGIN_REGISTRAR_EVENTS_H

#include <dirsrv/slapi-plugin.h>
#include "plugin_registrar_status.h"

///
/// @brief
/// @param block
///
void on_registration_success(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @param error
///
void on_registration_failure(Slapi_PBlock* block, plugin_registrar_error_t error);

#endif  // PLUGIN_REGISTRAR_EVENTS_H
