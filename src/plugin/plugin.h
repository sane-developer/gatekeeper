#ifndef GATEKEEPER_PLUGIN_H
#define GATEKEEPER_PLUGIN_H

///
/// @brief Initializes the resources required to properly run the plugin.
/// @return 0, when the plugin is successfully initialized; otherwise, 1.
///
int initialize_plugin();

///
/// @brief Evaluates the incoming bind request based on the plugin's binding policy.
/// @return 0, when the bind request is permitted; otherwise, 1.
///
int evaluate_bind_request();

#endif