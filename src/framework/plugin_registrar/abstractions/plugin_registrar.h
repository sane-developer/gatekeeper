#ifndef PLUGIN_REGISTRAR_H
#define PLUGIN_REGISTRAR_H

#include "aci_rule.h"
#include "bind_request_status.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

///
/// @brief
///
typedef bind_request_status_t (*bind_request_handler_t)(Slapi_PBlock*);

///
/// @brief
/// @param block
/// @param identity
/// @return
///
bool get_plugin_identity(Slapi_PBlock* block, Slapi_ComponentId* identity);

///
/// @brief
/// @param block
/// @param description
/// @return
///
bool set_plugin_description(Slapi_PBlock* block, Slapi_PluginDesc* description);

///
/// @brief
/// @param block
/// @return
///
bool set_plugin_ldap_protocol_version(Slapi_PBlock* block);

///
/// @brief
/// @param block
/// @return
///
bool set_plugin_bind_request_handler(Slapi_PBlock* block, bind_request_handler_t handler);

///
/// @brief
/// @param block
/// @param grant_rules
/// @param deny_rules
/// @return
///
bool set_plugin_aci_rules(Slapi_PBlock* block, aci_rules_t* grant_rules, aci_rules_t* deny_rules);

#endif  // PLUGIN_REGISTRAR_H
