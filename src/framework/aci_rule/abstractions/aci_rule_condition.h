#ifndef ACI_RULE_CONDITION_H
#define ACI_RULE_CONDITION_H

#include "aci_rule_operand.h"
#include "aci_rule_operation.h"
#include "aci_rule_parameter.h"
#include <stdbool.h>

///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    aci_rule_parameter_t parameter;

    ///
    /// @brief
    ///
    aci_rule_operation_t operation;

    ///
    /// @brief
    ///
    aci_rule_operands_t* operands;
}
aci_rule_condition_t;

///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    aci_rule_condition_t** items;

    ///
    /// @brief
    ///
    size_t capacity;

    ///
    /// @brief
    ///
    size_t count;
}
aci_rule_conditions_t;

///
/// @brief
/// @param condition
/// @param dn
/// @return
///
typedef bool (*dn_operation)(const aci_rule_operands_t*, const char*);

///
/// @brief
/// @param condition
/// @param ip
/// @return
///
typedef bool (*ip_operation)(const aci_rule_operands_t*, const PRNetAddr*);

///
/// @brief
/// @param condition
/// @param dns
/// @return
///
typedef bool (*dns_operation)(const aci_rule_operands_t*, const PRNetAddr*);

///
/// @brief
/// @param condition
/// @param roles
/// @return
///
typedef bool (*roles_operation)(const aci_rule_operands_t*, const char**);

///
/// @brief
/// @param condition
/// @param groups
/// @return
///
typedef bool (*groups_operation)(const aci_rule_operands_t*, const char**);

///
/// @brief
/// @param condition
/// @param attributes
/// @return
///
typedef bool (*attributes_operation)(const aci_rule_operands_t*, const char**);

///
/// @brief
/// @param condition
/// @param datetime
/// @return
///
typedef bool (*day_of_week_operation)(const aci_rule_operands_t*, const PRExplodedTime*);

///
/// @brief
/// @param condition
/// @param datetime
/// @return
///
typedef bool (*time_of_day_operation)(const aci_rule_operands_t*, const PRExplodedTime*);

///
/// @brief
/// @param operatioon
/// @return
///
dn_operation get_dn_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operatioon
/// @return
///
ip_operation get_ip_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operatioon
/// @return
///
dns_operation get_dns_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operatioon
/// @return
///
roles_operation get_roles_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operatioon
/// @return
///
groups_operation get_groups_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operatioon
/// @return
///
attributes_operation get_attributes_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operatioon
/// @return
///
day_of_week_operation get_day_of_week_operation(aci_rule_operation_t operation);

///
/// @brief
/// @param operatioon
/// @return
///
time_of_day_operation get_time_of_day_operation(aci_rule_operation_t operation);

#endif  // ACI_RULE_CONDITION_H
