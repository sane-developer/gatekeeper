#ifndef GATEKEEPER_BINDING_POLICY_H
#define GATEKEEPER_BINDING_POLICY_H

#include "array.h"

///
/// @brief Represents
///
typedef struct
{
    char** items;
    size_t capacity;
    size_t count;
}
binding_rule_filter_values_t;

///
/// @brief Represents a set of
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
/// @brief Represents a filter which determines the conditions of eligibility for accessing the server resources.
///
typedef struct
{
    binding_rule_filter_type_t type;
    binding_rule_filter_values_t* values;
}
binding_rule_filter_t;

///
/// @brief Represents a set of filters applicable to binding rules.
///
typedef struct
{
    binding_rule_filter_t** items;
    size_t capacity;
    size_t count;
}
binding_rule_filters_t;

///
/// @brief Represents a rule that regulates the clients access to the server resources.
///
typedef struct
{
    char* label;
    binding_rule_filters_t* apply_filters;
    binding_rule_filters_t* authorize_filters;
}
binding_rule_t;

///
/// @brief Represents a set of binding rules.
///
typedef struct
{
    binding_rule_t** items;
    size_t capacity;
    size_t count;
}
binding_rules_t;

///
/// @brief Represents a policy defining the logging behavior of the plugin.
///
typedef struct
{
    binding_rules_t* allow_rules;
    binding_rules_t* deny_rules;
}
binding_policy_t;

#endif //GATEKEEPER_BINDING_POLICY_H
