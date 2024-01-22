#ifndef GATEKEEPER_BINDING_POLICY_H
#define GATEKEEPER_BINDING_POLICY_H

#include <stddef.h>

///
/// @brief Represents the types of filters applicable to binding rules.
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
/// @brief Represents the set of values applicable to binding rule filters.
///
typedef struct
{
    char** items;
    size_t capacity;
    size_t count;
}
binding_rule_filter_values_t;

///
/// @brief Represents the model of binding rule filter.
///
typedef struct
{
    binding_rule_filter_type_t type;
    binding_rule_filter_values_t* values;
}
binding_rule_filter_t;

///
/// @brief Represents the set of filters applicable to binding rules.
///
typedef struct
{
    binding_rule_filter_t** items;
    size_t capacity;
    size_t count;
}
binding_rule_filters_t;

///
/// @brief Represents the types of binding rules.
///
typedef enum
{
    unknown_rule,
    allow_rule,
    deny_rule
}
binding_rule_type_t;

///
/// @brief Represents the model of a binding rule applicable to the binding rule set.
///
typedef struct
{
    char* label;
    binding_rule_type_t type;
    binding_rule_filters_t* user_filters;
    binding_rule_filters_t* authentication_filters;
}
binding_rule_t;

///
/// @brief Represents a set of unique binding rules.
///
typedef struct
{
    binding_rule_t** items;
    size_t capacity;
    size_t count;
}
binding_ruleset_t;

///
/// @brief Represents the model of binding policy configuration.
///
typedef struct
{
    binding_ruleset_t* allow_ruleset;
    binding_ruleset_t* deny_ruleset;
}
binding_policy_t;

///
/// @brief Allocates the binding policy on the heap.
/// @return The pointer to newly allocated binding policy.
///
binding_policy_t* create_binding_policy();

///
/// @brief Disposes the allocated binding policy.
/// @param policy The pointer to the allocated binding policy.
///
void dispose_binding_policy(binding_policy_t* policy);

#endif