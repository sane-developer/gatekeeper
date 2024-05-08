#ifndef ACI_RULE_OPERATION_PROVIDER_H
#define ACI_RULE_OPERATION_PROVIDER_H

#include "aci_rule_operand.h"
#include "aci_rule_operation.h"
#include "aci_rule_parameter.h"
#include "bind_request.h"
#include <stdbool.h>

///
/// @brief
///
typedef bool (*aci_rule_operation)(const aci_rule_operand_t*, const bind_request_t*);

///
/// @brief
/// @param parameter
/// @param operation
/// @return
///
aci_rule_operation get_aci_rule_operation(aci_rule_parameter_t parameter, aci_rule_operation_t operation);

#endif  // ACI_RULE_OPERATION_PROVIDER_H
