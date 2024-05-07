#include "aci_rule.h"
#include "bind_request.h"
#include <stdbool.h>


///
/// @brief
/// @param rule
/// @param request
/// @return
///
bool has_excluded(const aci_rule_t* rule, const bind_request_t* request);

///
/// @brief
/// @param rule
/// @param request
/// @return
///
bool has_applied(const aci_rule_t* rule, const bind_request_t* request);

///
/// @brief
/// @param rule
/// @param request
/// @return
///
bool has_satisfied(const aci_rule_t* rule, const bind_request_t* request);


