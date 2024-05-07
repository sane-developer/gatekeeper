#ifndef BIND_REQUEST_EVALUATOR_H
#define BIND_REQUEST_EVALUATOR_H

#include "aci_rule.h"
#include "bind_request.h"
#include "bind_request_status.h"

///
/// @brief
/// @param rules
/// @param request
/// @return
///
bind_request_status_t satisfies_grant_rules(const aci_rules_t* rules, bind_request_t* request);

///
/// @brief
/// @param rules
/// @param request
/// @return
///
bind_request_status_t satisfies_deny_rules(const aci_rules_t* rules, bind_request_t* request);

#endif  // BIND_REQUEST_EVALUATOR_H
