#ifndef GATEKEEPER_ACI_RULES_SUPPLIER_H_
#define GATEKEEPER_ACI_RULES_SUPPLIER_H_

#include "aci_rule.h"

///
/// @brief Supplies the custom ACI rules defined via user-defined format from user-defined storage.
/// @param block Pointer to operation parameters retrieved from the directory server.
/// @param grant_aci_rules Pointer to the collection of custom ACI rules of grant type.
/// @param deny_aci_rules Pointer to the collection of custom ACI rules of deny type.
/// @return
///     - 1, when the custom ACI rules have been successfully supplied.
///     - 0, otherwise.
///
int supply_custom_aci_rules(Slapi_PBlock* block, aci_rules_t* grant_aci_rules, aci_rules_t* deny_aci_rules);

#endif  // GATEKEEPER_ACI_RULES_SUPPLIER_H_
