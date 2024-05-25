#ifndef PLUGIN_REGISTRATION_HANDLER_H
#define PLUGIN_REGISTRATION_HANDLER_H

#include "aci_rule.h"
#include "bind_request_status.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

typedef bind_request_status_t (*bind_request_handler_t)(Slapi_PBlock*);

bool get_plugin_identity(
    Slapi_PBlock* block,
    Slapi_ComponentId* identity
);

bool set_plugin_description(
    Slapi_PBlock* block,
    Slapi_PluginDesc* description
);

bool set_plugin_ldap_protocol_version(
    Slapi_PBlock* block
);

bool set_plugin_bind_request_handler(
    Slapi_PBlock* block,
    bind_request_handler_t handler
);

bool set_plugin_bind_policy(
    Slapi_PBlock* block,
    aci_rule_linked_list_t* grant_rules,
    aci_rule_linked_list_t* deny_rules
);

#endif  // PLUGIN_REGISTRATION_HANDLER_H
