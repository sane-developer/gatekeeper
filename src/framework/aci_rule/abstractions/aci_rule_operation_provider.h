#ifndef ACI_RULE_OPERATION_PROVIDER_H
#define ACI_RULE_OPERATION_PROVIDER_H

#include "aci_rule_operand.h"
#include "aci_rule_operation_type.h"
#include "aci_rule_resource_type.h"
#include "bind_request.h"
#include <stdbool.h>

///
/// @brief
///
typedef bool (*aci_rule_operation_t)(const aci_rule_operand_t*, const bind_request_t*);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_dn_operation(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_ip_operation(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_dns_operation(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_roles_operation(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_groups_operation(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_attributes_operation(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_day_of_week_operation(aci_rule_operation_type_t operation);

///
/// @brief
/// @param operation
/// @return
///
aci_rule_operation_t get_time_of_day_operation(aci_rule_operation_type_t operation);

///
/// @brief
/// @param parameter
/// @param operation
/// @return
///
aci_rule_operation_t get_operation(aci_rule_resource_type_t resource, aci_rule_operation_type_t operation);

#endif  // ACI_RULE_OPERATION_PROVIDER_H
