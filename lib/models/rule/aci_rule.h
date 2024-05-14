#ifndef ACI_RULE_H
#define ACI_RULE_H

#include "aci_rule_expression.h"

///
/// @brief
///
struct aci_rule_t
{
    ///
    /// @brief
    ///
    char* label;

    ///
    /// @brief
    ///
    struct aci_rule_expression_t* exclude[MAX_EXPRESSIONS_COUNT];

    ///
    /// @brief
    ///
    struct aci_rule_expression_t* apply[MAX_EXPRESSIONS_COUNT];

    ///
    /// @brief
    ///
    struct aci_rule_expression_t* bind[MAX_EXPRESSIONS_COUNT];

    ///
    /// @brief
    ///
    struct aci_rule_t* next;
};

#endif  // ACI_RULE_H
