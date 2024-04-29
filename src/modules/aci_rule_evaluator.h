#ifndef ACI_RULE_EVALUATOR_H_
#define ACI_RULE_EVALUATOR_H_

#include "aci_rule.h"
#include "bind_request.h"

///
/// @brief Evaluates the bind request against the custom ACI rules of grant type.
/// @param rules Pointer to a collection of custom ACI rules of grant type.
/// @param request Pointer to a bind_request_t variable that stores the LDAP client and connection parameters.
/// @return
///     - REQUEST_GRANTED, when bind request did not trigger any of the ACI rules.
///     - REQUEST_DENIED, when bind request did not satisfy any of the bind conditions of single ACI rule.
///
bind_request_status_t evaluate_grant_aci_rules(const aci_rules_t* rules, bind_request_t* request);

///
/// @brief Evaluates the bind request against the custom ACI rules of deny type.
/// @param rules Pointer to a collection of custom ACI rules of deny type.
/// @param request Pointer to a bind_request_t variable that stores the LDAP client and connection parameters.
/// @return
///     - REQUEST_GRANTED, when bind request did not trigger any of the ACI rules.
///     - REQUEST_DENIED, when bind request satisfied any of the bind conditions of single ACI rule.
///
bind_request_status_t evaluate_deny_aci_rules(const aci_rules_t* rules, bind_request_t* request);

#endif  // ACI_RULE_EVALUATOR_H_
