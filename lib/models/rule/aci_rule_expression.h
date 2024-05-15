#ifndef ACI_RULE_EXPRESSION_H
#define ACI_RULE_EXPRESSION_H

#include "aci_rule_operand.h"
#include "aci_rule_operand_type.h"
#include "aci_rule_operator_type.h"
#include "aci_rule_operation_type.h"

///
/// @brief
///
#define MAX_EXPRESSIONS_COUNT 10

///
/// @brief
///
struct aci_rule_expression_t
{
    ///
    /// @brief
    ///
    aci_rule_operand_value_t values[MAX_OPERANDS_COUNT];

    ///
    /// @brief
    ///
    aci_rule_operand_type_t operand;

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
    struct aci_rule_expression_t* next;
};

#endif  // ACI_RULE_EXPRESSION_H
