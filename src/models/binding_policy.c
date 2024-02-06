#include "binding_policy.h"
#include "../allocators/allocator.h"

static inline void dispose_rule_filter_value_internals(void* item)
{
    string_t* value = (string_t*) item;

    dispose_string(value);
}

static inline void dispose_rule_filter_internals(void* item)
{
    binding_rule_filter_t* filter = (binding_rule_filter_t*) item;

    dispose_complex_array(filter->values, dispose_rule_filter_value_internals);
}

static inline void dispose_rule_internals(void* item)
{
    binding_rule_t* rule = (binding_rule_t*) item;

    dispose_complex_array(rule->apply_when, dispose_rule_filter_internals);
    dispose_complex_array(rule->authenticate_when, dispose_rule_filter_internals);
}

void dispose_binding_policy(binding_policy_t* policy)
{
    dispose_complex_array(policy->allow_rules, dispose_rule_internals);
    dispose_complex_array(policy->deny_rules, dispose_rule_internals);

    free_memory(policy);
}

binding_rule_filter_t* create_binding_rule_filter()
{
    const size_t filter_size = sizeof(binding_rule_filter_t);
    const size_t value_size = sizeof(string_t);
    const size_t value_set_capacity = 16;

    binding_rule_filter_t* filter = (binding_rule_filter_t*) allocate_memory(filter_size);

    filter->values = array_from_size(value_set_capacity, value_size);

    return filter;
}

binding_rule_t* create_binding_rule()
{
    const size_t rule_size = sizeof(binding_rule_t);
    const size_t filter_size = sizeof(binding_rule_filter_t);
    const size_t supported_filters_count = 9;

    binding_rule_t* rule = (binding_rule_t*) allocate_memory(rule_size);

    rule->apply_when = array_from_size(supported_filters_count, filter_size);
    rule->authenticate_when = array_from_size(supported_filters_count, filter_size);

    return rule;
}

binding_policy_t* create_binding_policy()
{
    const size_t policy_size = sizeof(binding_policy_t);
    const size_t rule_size = sizeof(binding_rule_t);
    const size_t rule_set_capacity = 16;

    binding_policy_t* policy = (binding_policy_t*) allocate_memory(policy_size);

    policy->allow_rules = array_from_size(rule_set_capacity, rule_size);
    policy->deny_rules = array_from_size(rule_set_capacity, rule_size);

    return policy;
}