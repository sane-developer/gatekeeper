#ifndef PLUGIN_H
#define PLUGIN_H

#include "bind_request.h"

///
/// @brief
///
typedef enum
{
    PLUGIN_REGISTERED = 0,

    PLUGIN_UNREGISTERED = 1,
}
plugin_registration_status_t;

///
/// @brief
///
typedef enum
{
    PLUGIN_IDENTITY_SETUP_FAILURE,

    PLUGIN_DESCRIPTION_SETUP_FAILURE,

    PLUGIN_LDAP_PROTOCOL_VERSION_SETUP_FAILURE,

    PLUGIN_BIND_REQUEST_HANDLER_SETUP_FAILURE,

    PLUGIN_BIND_POLICY_SETUP_FAILURE
}
plugin_registration_handler_error_t;

///
/// @brief
///
typedef struct
{
    Slapi_PBlock* block;
}
on_plugin_registered_event_args_t;

///
/// @brief
///
typedef struct
{
    Slapi_PBlock* block;

    plugin_registration_handler_error_t error;
}
on_plugin_unregistered_event_args_t;

///
/// @brief
/// @param args
///
void on_plugin_registered(const on_plugin_registered_event_args_t* args);

///
/// @brief
/// @param args
///
void on_plugin_unregistered(const on_plugin_unregistered_event_args_t* args);

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
