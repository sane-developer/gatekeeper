#ifndef BIND_REQUEST_HANDLER_H
#define BIND_REQUEST_HANDLER_H

#include "aci_rule.h"
#include "bind_request_status.h"
#include <dirsrv/slapi-plugin.h>

///
/// @brief
/// @param block
/// @param grant_rules
/// @param deny_rules
/// @return
///
bind_request_status_t handle_bind_request(Slapi_PBlock* block, aci_rules_t* grant_rules, aci_rules_t* deny_rules);

#endif  // BIND_REQUEST_HANDLER_H
