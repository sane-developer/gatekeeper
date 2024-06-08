#include "plugin.h"

aci_rules_t plugin_deny_aci_rules = {0};

aci_rules_t plugin_grant_aci_rules = {0};

Slapi_ComponentId* plugin_component_identity = NULL;

Slapi_PluginDesc plugin_component_description = {0};
