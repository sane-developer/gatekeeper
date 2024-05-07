#ifndef GATEKEEPER_ACI_RULE_PROVIDER_H
#define GATEKEEPER_ACI_RULE_PROVIDER_H

#include <dirsrv/slapi-plugin.h>
#include "aci_rule.h"

int fetch_custom_aci_rules(Slapi_PBlock* block, aci_rules_t* grant_rules, aci_rules_t* deny_rules);

#endif  // GATEKEEPER_ACI_RULE_PROVIDER_H
