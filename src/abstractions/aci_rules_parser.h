#ifndef ACI_RULES_PARSER_H_
#define ACI_RULES_PARSER_H_

#include "aci_rule.h"

///
/// @brief Parses the ACI rules represented in user-defined format and stored in user-defined location.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @param grant_aci_rules Pointer to a collection of custom ACI rules that determine whether bind request should be granted.
/// @param deny_aci_rules Pointer to a collection of custom ACI rules that determine whether bind request should be denied.
/// @return
///     - 1, when the ACI rules have been parsed successfully.
///     - 0, when any error has occured during the ACI rules parsing.
///
int parse_custom_aci_rules(Slapi_PBlock* block, aci_rules_t* grant_aci_rules, aci_rules_t* deny_aci_rules);

#endif  // ACI_RULES_PARSER_H_
