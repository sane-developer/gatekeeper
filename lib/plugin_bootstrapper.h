#ifndef PLUGIN_BOOTSTRAPPER_H
#define PLUGIN_BOOTSTRAPPER_H

#include "aci_rule.h"
#include "bind_request.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

typedef enum
{
    REGISTERED_PLUGIN,

    FAILED_TO_GET_PLUGIN_IDENTITY,

    FAILED_TO_SET_PLUGIN_DESCRIPTION,

    FAILED_TO_SET_PLUGIN_LDAP_PROTOCOL_VERSION,

    FAILED_TO_SET_PLUGIN_BIND_REQUEST_HANDLER,

    FAILED_TO_SET_PLUGIN_BIND_POLICY
}
plugin_bootstrapper_status_t, plugin_bootstrapper_error_t;

typedef bind_request_status_t (*bind_request_handler_t)(Slapi_PBlock*);

bool get_plugin_identity(Slapi_PBlock* block, Slapi_ComponentId* identity);

bool set_plugin_description(Slapi_PBlock* block, Slapi_PluginDesc* description);

bool set_plugin_ldap_protocol_version(Slapi_PBlock* block);

bool set_plugin_bind_request_handler(Slapi_PBlock* block, bind_request_handler_t handler);

bool set_plugin_bind_policy(Slapi_PBlock* block, aci_rule_t* grant_rules, aci_rule_t* deny_rules);

typedef struct
{
    Slapi_PBlock* block;
}
finished_registration_event_args_t;

typedef struct
{
    Slapi_PBlock* block;

    plugin_bootstrapper_error_t error;
}
aborted_registration_event_args_t;

void on_finished_registration(finished_registration_event_args_t args);

void on_aborted_registration(aborted_registration_event_args_t args);

#endif  // PLUGIN_BOOTSTRAPPER_H
