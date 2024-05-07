#ifndef PLUGIN_REGISTRAR_ACTIONS_H
#define PLUGIN_REGISTRAR_ACTIONS_H

#include <dirsrv/slapi-plugin.h>
#include "plugin_registrar_status.h"

///
/// @brief
/// @param block
/// @return
///
plugin_registrar_status_t register_plugin(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @param error
/// @return
///
plugin_registrar_status_t cancel_registration(Slapi_PBlock* block, plugin_registrar_error_t error);

#endif  // PLUGIN_REGISTRAR_ACTIONS_H
