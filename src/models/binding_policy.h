#ifndef GATEKEEPER_BINDING_POLICY_H
#define GATEKEEPER_BINDING_POLICY_H

#include "../utilities/array.h"
#include "../utilities/string.h"

///
/// @brief
///
typedef enum
{
    unsupported_rule,
    allow_rule,
    deny_rule
}
binding_rule_type_t;

///
/// @brief
///
typedef enum
{
    unsupported_filter,
    user_dn_filter,
    user_ip_filter,
    user_role_filter,
    user_group_filter,
    user_attributes_filter,
    dns_filter,
    day_of_week_filter,
    time_of_day_filter,
    authentication_method_filter
}
binding_rule_filter_type_t;

///
/// @brief
///
typedef struct
{
    string_t** items;
    size_t capacity;
    size_t count;
}
binding_rule_filter_values_t;

///
/// @brief
///
typedef struct
{
    binding_rule_filter_type_t type;
    binding_rule_filter_values_t* values;
}
binding_rule_filter_t;

///
/// @brief
///
typedef struct
{
    binding_rule_filter_t** items;
    size_t capacity;
    size_t count;
}
binding_rule_filters_t;

///
/// @brief
///
typedef struct
{
    string_t* label;
    binding_rule_type_t type;
    binding_rule_filters_t* apply_when;
    binding_rule_filters_t* authenticate_when;
}
binding_rule_t;

///
/// @brief
///
typedef struct
{
    binding_rule_t** items;
    size_t capacity;
    size_t count;
}
binding_rules_t;

///
/// @brief
///
typedef struct
{
    binding_rules_t* allow_rules;
    binding_rules_t* deny_rules;
}
binding_policy_t;

///
/// @brief
/// @return
///
binding_policy_t* create_binding_policy();

///
/// @brief
/// @return
///
binding_rule_t* create_binding_rule();

///
/// @brief
/// @return
///
binding_rule_filter_t* create_binding_rule_filter();

///
/// @brief
/// @param
///
void dispose_binding_policy(binding_policy_t* policy);

#endif