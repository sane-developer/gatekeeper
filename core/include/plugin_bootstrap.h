#ifndef PLUGIN_BOOTSTRAP_H
#define PLUGIN_BOOTSTRAP_H

#include "plugin_registration.h"

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

#endif  // PLUGIN_BOOTSTRAP_H
