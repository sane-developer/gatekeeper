#ifndef ACI_RULE_H_
#define ACI_RULE_H_

#include "aci_rule_condition.h"

///
/// @brief Represents a custom ACI rule.
///
typedef struct
{
    ///
    /// @brief Pointer to a string representing the name of the ACI rule.
    ///
    char* label;

    ///
    /// @brief Pointer to a collection of conditions that determine whether the rule should skip evaluated bind request.
    ///
    aci_rule_conditions_t* exclude;

    ///
    /// @brief Pointer to a collection of conditions that determine whether the rule should be applied to evaluated bind request.
    ///
    aci_rule_conditions_t* apply;

    ///
    /// @brief Pointer to a collection of conditions that determine whether the bind request should be denied.
    ///
    aci_rule_conditions_t* bind;
}
aci_rule_t;

///
/// @brief Represents a collection of custom ACI rules.
///
typedef struct
{
    ///
    /// @brief Pointer to a collection of custom ACI rules.
    ///
    aci_rule_t** items;

    ///
    /// @brief Numerical value that represents the capacity of the collection.
    ///
    size_t capacity;
    
    ///
    /// @brief Numerical value that represents the count of the stored items.
    ///
    size_t count;
}
aci_rules_t;

#endif  // ACI_RULE_H_
