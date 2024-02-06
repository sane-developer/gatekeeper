#ifndef GATEKEEPER_LOGGING_POLICY_SUPPLIER_H
#define GATEKEEPER_LOGGING_POLICY_SUPPLIER_H

#include "../models/logging_policy.h"

///
/// @brief
/// @param resource
/// @return
///
logging_policy_t* supply_logging_policy(void* resource);

#endif