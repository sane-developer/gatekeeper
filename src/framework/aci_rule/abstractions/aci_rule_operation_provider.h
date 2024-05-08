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
/// @param operation
/// @return
///
aci_rule_operation get_dn_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation get_ip_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation get_dns_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation get_roles_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation get_groups_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation get_attributes_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation get_day_of_week_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation get_time_of_day_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param parameter
/// @param operation
/// @return
///
aci_rule_operation get_operation(aci_rule_parameter_t parameter, aci_rule_operation_t operation);

#endif  // ACI_RULE_OPERATION_PROVIDER_H
