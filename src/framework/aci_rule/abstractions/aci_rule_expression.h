#ifndef ACI_RULE_EXPRESSION_H
#define ACI_RULE_EXPRESSION_H

#include "aci_rule_operand.h"
#include "aci_rule_operator.h"
#include "aci_rule_operation.h"
#include "aci_rule_parameter.h"

///
/// @brief
///
#define MAXIMUM_OPERANDS_COUNT 5

///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    aci_rule_operand_t operands[MAXIMUM_OPERANDS_COUNT];

    ///
    /// @brief
    ///
    aci_rule_operator_t operator;

    ///
    /// @brief
    ///
    aci_rule_operation_t operation;

    ///
    /// @brief
    ///
    aci_rule_parameter_t parameter;

    ///
    /// @brief
    ///
    struct aci_rule_expression_t* next;
}
aci_rule_expression_t;

#endif  // ACI_RULE_EXPRESSION_H
