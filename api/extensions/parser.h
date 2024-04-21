#ifndef GATEKEEPER_PARSER_H_
#define GATEKEEPER_PARSER_H_

#include <slapi-plugin.h>

///
/// @brief Sets processed ACI rules to respective containers.
/// @param block Pointer to the operation parameters block.
/// @param grant_aci_rules Pointer to the contaienr of ACI rules of grant type.
/// @param deny_aci_rules Pointer to the container of ACI rules of deny type.
/// @return
///     - 1 when ACI rules were set successfully.
///     - 0 when error occured during parsing routine.
/// TODO: Switch void* to appropriate aci rules type when implemented.
///
int set_aci_rules(Slapi_PBlock* block, void* grant_aci_rules, void* deny_aci_rules);

#endif  // GATEKEEPER_PARSER_H_
