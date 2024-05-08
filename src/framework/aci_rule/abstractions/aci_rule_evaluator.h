#ifndef ACI_RULE_EVALUATOR_H
#define ACI_RULE_EVALUATOR_H

#include "aci_rule.h"
#include "bind_request.h"
#include <stdbool.h>

///
/// @brief
/// @param rule
/// @param request
/// @return
///
bool has_applied_rule(const aci_rule_t* rule, const bind_request_t* request);

///
/// @brief
/// @param rule
/// @param request
/// @return
///
bool has_satisfied_rule(const aci_rule_t* rule, const bind_request_t* request);

#endif  // ACI_RULE_EVALUATOR_H
