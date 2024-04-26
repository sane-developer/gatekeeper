#ifndef ACI_RULE_H_
#define ACI_RULE_H_

#include "aci_rule_condition.h"
#include "bind_request.h"

///
/// @brief Represents an extended ACI rule.
///
typedef struct
{
    ///
    /// @brief Pointer to a string that uniquely identifies the ACI rule.
    ///
    char* label;

    ///
    /// @brief Pointer to a collection of ACI conditions that determine whether the ACI rule should be applied.
    ///
    aci_rule_conditions_t* apply;

    ///
    /// @brief Pointer to a collection of ACI conditions that determine whether the bind request should be granted.
    ///
    aci_rule_conditions_t* bind;
}
aci_rule_t;

///
/// @brief Represents a collection of extended ACI rules.
///
typedef struct
{
    ///
    /// @brief Pointer to the head of collection of pointers to aci_rule_t variables.
    ///
    aci_rule_t** items;

    ///
    /// @brief Number of aci_rule_t variables that may be stored in the collection.
    ///
    size_t capacity;

    ///
    /// @brief Number of aci_rule_t variables that are currently stored in the collction.
    ///
    size_t count;
}
aci_rules_t;

///
/// @brief
/// @param rule
/// @param request
/// @return
///     - 1, when .
///     - 0, when .
///
int has_applied_aci_rule(const aci_rule_t* rule, const bind_request_t* request);

///
/// @brief
/// @param rule
/// @param request
/// @return
///     - 1, when .
///     - 0, when .
///
int has_triggered_aci_rule(const aci_rule_t* rule, const bind_request_t* request);

#endif  // ACI_RULE_H_
