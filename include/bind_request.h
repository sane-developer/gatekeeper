#ifndef GATEKEEPER_BIND_REQUEST_H
#define GATEKEEPER_BIND_REQUEST_H

#include "binding_policy.h"

///
/// @brief
///
typedef struct
{

}
bind_request_t;

///
/// @brief
/// @param request
/// @param rule
/// @return
///
int respects_binding_rule(const bind_request_t* request, const binding_rule_t* rule);

int respects_user_dn_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

int respects_user_ip_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

int respects_user_role_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

int respects_user_group_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

int respects_user_attrs_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

int respects_user_attrs_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

int respects_user_attrs_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

int respects_user_attrs_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

int respects_user_attrs_conditions(const bind_request_t* request, const binding_rule_filter_values_t* values);

#endif //GATEKEEPER_BIND_REQUEST_H
