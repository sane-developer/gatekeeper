#ifndef GATEKEEPER_ACI_RULES_EVALUATOR_H_
#define GATEKEEPER_ACI_RULES_EVALUATOR_H_

#include "aci_rule.h"
#include "bind_request.h"

///
/// @brief Determines whether bind request satisfies applied grant ACI rules.
/// @param rules Pointer to the head of collection of pointers to aci_rules_t variables of grant type.
/// @param request Pointer to the populated bind_request_t variable.
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
/// @param rules Pointer to the head of collection of pointers to aci_rules_t variables of deny type.
/// @param request Pointer to the populated bind_request_t variable.
/// @return
///     - SATISFIED_DENY_ACI_RULES, when request did not meet any of bind conditions of applied ACI rules.
///     - REQUEST_DENIED, otherwise.
///
/// @remark
///     - If REQUEST_DENIED was returned; the label of the violated ACI rule is copied into bind_request_t "note" field.
///
bind_request_state_t satisfies_deny_aci_rules(const aci_rules_t* rules, bind_request_t* request);

#endif  // GATEKEEPER_ACI_RULES_EVALUATOR_H_
