#ifndef ACI_RULE_H
#define ACI_RULE_H

#include "aci_rule_condition.h"

///
/// @brief
///
#define MAXIMUM_CONDITIONS_COUNT 10

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
    aci_rule_condition_t* exclude[MAXIMUM_CONDITIONS_COUNT];

    ///
    /// @brief
    ///
    aci_rule_condition_t* apply[MAXIMUM_CONDITIONS_COUNT];

    ///
    /// @brief
    ///
    aci_rule_condition_t* bind[MAXIMUM_CONDITIONS_COUNT];
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
