#ifndef ACI_RULE_H_
#define ACI_RULE_H_

#include "aci_condition.h"
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
    aci_conditions_t* apply;

    ///
    /// @brief Pointer to a collection of ACI conditions that determine whether the bind request should be granted.
    ///
    aci_conditions_t* bind;
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
/// @brief Determines whether bind request satisfies applied grant ACI rules.
///
/// @param rules Pointer to the head of collection of pointers to aci_rules_t variables of grant type.
/// @param request Pointer to the populated bind_request_t variable.
///
/// @return
///     - SATISFIED_GRANT_ACI_RULES, when request met all of the bind conditions of applied ACI rules.
///     - REQUEST_DENIED, otherwise.
///
/// @remark
///     - If REQUEST_DENIED was returned; the label of the violated ACI rule is copied into bind_request_t "note" field.
///
bind_request_state_t satisfies_grant_aci_rules(const aci_rules_t* rules, bind_request_t* request);

///
/// @brief Determines whether bind request satisfies applied deny ACI rules.
///
/// @param rules Pointer to the head of collection of pointers to aci_rules_t variables of deny type.
/// @param request Pointer to the populated bind_request_t variable.
///
/// @return
///     - SATISFIED_DENY_ACI_RULES, when request did not meet any of bind conditions of applied ACI rules.
///     - REQUEST_DENIED, otherwise.
///
/// @remark
///     - If REQUEST_DENIED was returned; the label of the violated ACI rule is copied into bind_request_t "note" field.
///
bind_request_state_t satisfies_deny_aci_rules(const aci_rules_t* rules, bind_request_t* request);

#endif  // ACI_RULE_H_
