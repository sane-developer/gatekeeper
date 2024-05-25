#ifndef ACI_RULE_EVALUATOR_H
#define ACI_RULE_EVALUATOR_H

#include "aci_rule.h"
#include "bind_request.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

bool has_applied_rule(
    Slapi_PBlock* block,
    aci_rule_t* rule,
    bind_request_t* request
);

bool has_triggered_rule(
    Slapi_PBlock* block,
    aci_rule_t* rule,
    bind_request_t* request
);

#endif  // ACI_RULE_EVALUATOR_H
