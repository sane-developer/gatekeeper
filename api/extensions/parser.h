#ifndef GATEKEEPER_PARSER_H_
#define GATEKEEPER_PARSER_H_

///
/// @brief Supplies the plugin with the custom ACI rules crafted by the user.
/// @param grant_aci_rules The pointer to a contaienr of ACI rules of grant type.
/// @param deny_aci_rules The pointer to a container of ACI rules of deny type.  
/// @return 1, when the ACI rules have been successfully parsed; otherwise, 0. 
/// TODO: Switch void* to appropriate aci rules type when implemented.
///
int supply_aci_rules(void* grant_aci_rules, void* deny_aci_rules);

#endif  // GATEKEEPER_PARSER_H_
