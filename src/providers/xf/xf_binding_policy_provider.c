#include <stdio.h>
#include "../binding_policy_provider.h"
#include "../../includes/string.h"
#include "../../includes/flags.h"

#define RULE_DEFINITION_START_MARKER "{"
#define RULE_DEFINITION_END_MARKER "}"

typedef enum
{
    has_rule_label = 1 << 0,
    has_rule_type = 1 << 1,
    has_apply_when_filters = 1 << 2,
    has_authorize_when_filters = 1 << 3
}
rule_status_t;

typedef enum
{
    is_processing_rule = 1 << 0,
    is_processing_rule_label = 1 << 1,
    is_processing_rule_type = 1 << 2,
    is_processing_apply_when_filters = 1 << 3,
    is_processing_authorize_when_filters = 1 << 4
}
parser_status_t;

static inline parser_target_t map_entry_to_parser_target(const string_t* entry)
{
    if (matches_contents_of_string_literal(entry, "rule_label"))
    {
        return rule_label;
    }

    if (matches_contents_of_string_literal(entry, "rule_type"))
    {
        return rule_type;
    }

    if (matches_contents_of_string_literal(entry, "apply_when"))
    {
        return apply_when;
    }

    if (matches_contents_of_string_literal(entry, "authenticate_when"))
    {
        return authenticate_when;
    }

    return undefined_target;
}

static inline binding_rule_type_t map_entry_to_rule_type(const string_t* entry)
{
    if (matches_contents_of_string_literal(entry, "allow"))
    {
        return allow_rule;
    }

    if (matches_contents_of_string_literal(entry, "deny"))
    {
        return deny_rule;
    }

    return unsupported_rule;
}

static inline binding_rule_filter_type_t map_entry_to_rule_filter_type(const string_t* entry)
{
    if (matches_contents_of_string_literal(entry, "dn"))
    {
        return user_dn_filter;
    }

    if (matches_contents_of_string_literal(entry, "ip"))
    {
        return user_ip_filter;
    }

    if (matches_contents_of_string_literal(entry, "role"))
    {
        return user_role_filter;
    }

    if (matches_contents_of_string_literal(entry, "group"))
    {
        return user_group_filter;
    }

    if (matches_contents_of_string_literal(entry, "attr"))
    {
        return user_attributes_filter;
    }

    if (matches_contents_of_string_literal(entry, "dns"))
    {
        return dns_filter;
    }

    if (matches_contents_of_string_literal(entry, "dayofweek"))
    {
        return day_of_week_filter;
    }

    if (matches_contents_of_string_literal(entry, "timeofday"))
    {
        return time_of_day_filter;
    }

    if (matches_contents_of_string_literal(entry, "sasl"))
    {
        return authentication_method_filter;
    }

    return unsupported_filter;
}

static inline char matches_rule_definition_start_marker(const string_t* entry)
{
    return is_equal_to_string_literal(entry, RULE_DEFINITION_START_MARKER);
}

static inline char matches_rule_definition_end_marker(const string_t* entry)
{
    return is_equal_to_string_literal(entry, RULE_DEFINITION_END_MARKER);
}

static inline void initialize_empty_rule()
{

}

static inline void reset_rule()
{

}

static inline parser_events_t parse_file(FILE* file, binding_policy_t* policy)
{
    string_t* scattered = string_from_size(100);
    string_t* trimmed = string_from_size(100);

    while (fgets(scattered->item, scattered->length, file) != NULL)
    {
        erase_whitespaces_from_string(scattered, trimmed);

        if (matches_rule_definition_start_marker(trimmed))
        {
            initialize_empty_rule();
            continue;
        }

        if (matches_rule_definition_end_marker(trimmed))
        {
            reset_rule();
            continue;
        }
    }
}

static inline char validate(parser_status_t events, binding_policy_t* policy)
{
    return 0;
}

binding_policy_t* supply_binding_policy(void* resource)
{
    return NULL;
}