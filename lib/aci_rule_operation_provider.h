#ifndef ACI_RULE_OPERATION_PROVIDER_H
#define ACI_RULE_OPERATION_PROVIDER_H

#include "aci_rule_operand.h"
#include "aci_rule_operand_type.h"
#include "aci_rule_operation_type.h"
#include "bind_request.h"
#include <stdbool.h>

///
/// @brief
///
typedef bool (*aci_rule_operation_t)(aci_rule_operand_value_t*, bind_request_t*);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_dn_operand(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_ip_operand(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_dns_operand(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_role_operand(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_group_operand(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_attribute_operand(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_weekday_operand(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_time_operand(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operand
/// @param operation
/// @return
///
aci_rule_operation_t get_operation_for_operand(aci_rule_operand_type_t operand, aci_rule_operation_type_t operation);

#endif  // ACI_RULE_OPERATION_PROVIDER_H
