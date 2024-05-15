#ifndef BIND_REQUEST_EVALUATOR_H
#define BIND_REQUEST_EVALUATOR_H

#include "aci_rule.h"
#include "bind_request.h"
#include <stdbool.h>

///
/// @brief
/// @param block
/// @param request
/// @return
///
bool has_satisfied_grant_rules(struct aci_rule_t* rules, bind_request_t* request);

///
/// @brief
/// @param block
/// @param request
/// @return
///
bool has_satisfied_deny_rules(struct aci_rule_t* rules, bind_request_t* request);

#endif  // BIND_REQUEST_EVALUATOR_H
