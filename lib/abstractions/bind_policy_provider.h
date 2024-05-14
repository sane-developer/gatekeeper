#ifndef BIND_POLICY_PROVIDER_H
#define BIND_POLICY_PROVIDER_H

#include "bind_policy.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

///
/// @brief
/// @param block
/// @param policy
/// @return
///
bool set_plugin_bind_policy(Slapi_PBlock* block, bind_policy_t* policy);

#endif  // BIND_POLICY_PROVIDER_H
