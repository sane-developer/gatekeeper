#ifndef GATEKEEPER_PLUGIN_H
#define GATEKEEPER_PLUGIN_H

#include "providers/binding_policy_provider.h"
#include "providers/logging_policy_provider.h"

///
/// @brief
///
binding_policy_t* plugin_binding_policy;

///
/// @brief
///
logging_policy_t* plugin_logging_policy;

///
/// @brief
/// @return
///
int initialize_plugin();

///
/// @brief
/// @return
///
char evaluate_bind_request();

#endif