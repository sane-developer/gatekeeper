#ifndef GATEKEEPER_ACI_RULE_EVALUATOR_H
#define GATEKEEPER_ACI_RULE_EVALUATOR_H

#include "aci_rule.h"
#include "bind_request.h"
#include "bind_request_status.h"

bind_request_status_t evaluate_against_grant_rules(const aci_rules_t* rules, bind_request_t* request);

bind_request_status_t evaluate_against_deny_rules(const aci_rules_t* rules, bind_request_t* request);

#endif  // GATEKEEPER_ACI_RULE_EVALUATOR_H
