#ifndef ACI_RULE_CONDITION_H
#define ACI_RULE_CONDITION_H

#include "aci_rule_operand.h"
#include "aci_rule_operator_type.h"
#include "aci_rule_operation_type.h"
#include "aci_rule_resource_type.h"

///
/// @brief
///
#define MAXIMUM_CONDITIONS_COUNT 10

///
/// @brief
///
typedef struct aci_rule_expression_t
{
    ///
    /// @brief
    ///
    aci_rule_operand_t operands[MAXIMUM_OPERANDS_COUNT];

    ///
    /// @brief
    ///
    aci_rule_operator_type_t operator;

    ///
    /// @brief
    ///
    aci_rule_operation_type_t operation;

    ///
    /// @brief
    ///
    aci_rule_resource_type_t parameter;

    ///
    /// @brief
    ///
    struct aci_rule_expression_t* next;
}
aci_rule_condition_t;

#endif  // ACI_RULE_CONDITION_H
