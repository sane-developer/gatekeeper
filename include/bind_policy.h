#ifndef BIND_POLICY_H
#define BIND_POLICY_H

#include "aci_rule.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

///
/// @brief
///
typedef struct
{
    aci_rule_t grant_type_rules[RULES_LIMIT];

    aci_rule_t deny_type_rules[RULES_LIMIT];
}
bind_policy_t;

///
/// @brief
/// @param block
/// @param policy
/// @return
///
bool setup_bind_policy(
    Slapi_PBlock* block,
    bind_policy_t* policy
);

#endif  // BIND_POLICY_H
