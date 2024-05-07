#ifndef ACI_RULE_H
#define ACI_RULE_H

#include "aci_rule_condition.h"

///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    char* label;

    ///
    /// @brief
    ///
    aci_rule_conditions_t* exclude;

    ///
    /// @brief
    ///
    aci_rule_conditions_t* apply;

    ///
    /// @brief
    ///
    aci_rule_conditions_t* bind;
}
aci_rule_t;

///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    aci_rule_t** items;

    ///
    /// @brief
    ///
    size_t capacity;

    ///
    /// @brief
    ///
    size_t count;
}
aci_rules_t;

#endif  // ACI_RULE_H
