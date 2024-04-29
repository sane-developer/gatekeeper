#ifndef ACI_RULE_CONDITION_H_
#define ACI_RULE_CONDITION_H_

#include "aci_rule_condition_operand.h"
#include "aci_rule_condition_operation.h"
#include "aci_rule_condition_parameter.h"

///
/// @brief Represents a condition applied to custom ACI rule.
///
typedef struct
{
    ///
    /// @brief Numerical value that represents which bind request parameter should be evaluated.
    ///
    aci_rule_condition_parameter_t parameter;

    ///
    /// @brief Numerical value that represents which operation should be performed on the bind request parameter.
    ///
    aci_rule_condition_operation_t operation;

    ///
    /// @brief Pointer to a collection of operands that should be used to evaluate the bind request parameter.
    ///
    aci_rule_operands_t* operands;
}
aci_rule_condition_t;
///
/// @brief Represents a collection of custom ACI rules.
///
typedef struct
{
    ///
    /// @brief Pointer to a collection of custom ACI rules.
    ///
    aci_rule_condition_t** items;
    
    ///
    /// @brief Numerical value that represents the capacity of the collection.
    ///
    size_t capacity;
    
    ///
    /// @brief Numerical value that represents the count of the stored items.
    ///
    size_t count;
}
aci_rule_conditions_t;

#endif  // ACI_RULE_CONDITION_H_
