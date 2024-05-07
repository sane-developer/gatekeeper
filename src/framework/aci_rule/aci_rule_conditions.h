#ifndef GATEKEEPER_ACI_RULE_CONDITIONS_H
#define GATEKEEPER_ACI_RULE_CONDITIONS_H

#include <stdbool.h>
#include "aci_rule.h"

bool satisfies_dn_condition(const aci_rule_condition_t* condition, const char* dn);

bool satisfies_ip_condition(const aci_rule_condition_t* condition, const PRNetAddr* ip);

bool satisfies_dns_condition(const aci_rule_condition_t* condition, const PRNetAddr* dns);

bool satisfies_roles_condition(const aci_rule_condition_t* condition, const char** roles);

bool satisfies_groups_condition(const aci_rule_condition_t* condition, const char** groups);

bool satisfies_attributes_condition(const aci_rule_condition_t* condition, const char** attributes);

bool satisfies_day_of_week_condition(const aci_rule_condition_t* condition, const PRExplodedTime* datetime);

bool satisfies_time_of_day_condition(const aci_rule_condition_t* condition, const PRExplodedTime* datetime);

#endif  // GATEKEEPER_ACI_RULE_CONDITIONS_H
