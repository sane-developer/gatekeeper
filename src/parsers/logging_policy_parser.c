#include "logging_policy_parser.h"
#include "../types/string.h"
#include "../utilities/flags.h"

#define ENTRY_SIZE 100
#define STATE_SIZE sizeof(logging_policy_parser_state_t)

static inline logging_policy_parser_target_t map_label_to_parser_target(const string_t* label)
{
    if (matches_contents_of_string_literal(label, "accepted_requests_strategy"))
    {
        return accepted_requests_strategy;
    }

    if (matches_contents_of_string_literal(label, "denied_requests_strategy"))
    {
        return denied_requests_strategy;
    }

    return undefined_strategy;
}

static inline logging_option_t map_label_to_strategy_option(const string_t* label)
{
    if (matches_contents_of_string_literal(label, "ignore_logging"))
    {
        return ignore_logging;
    }

    if (matches_contents_of_string_literal(label, "include_rule_name"))
    {
        return include_rule_name;
    }

    if (matches_contents_of_string_literal(label, "include_user_dn"))
    {
        return include_user_dn;
    }

    if (matches_contents_of_string_literal(label, "include_user_ip"))
    {
        return include_user_ip;
    }

    if (matches_contents_of_string_literal(label, "include_evaluation"))
    {
        return include_evaluation;
    }

    if (matches_contents_of_string_literal(label, "include_date"))
    {
        return include_date;
    }

    if (matches_contents_of_string_literal(label, "include_authentication_method"))
    {
        return include_authentication_method;
    }

    if (matches_contents_of_string_literal(label, "include_sasl_method"))
    {
        return include_sasl_method;
    }

    return unsupported_option;
}

static inline char has_target(const logging_policy_parser_state_t* state)
{
    return state->target != undefined_strategy;
}

static inline void set_parser_target(logging_policy_parser_state_t* state, logging_policy_parser_target_t target)
{
    if (target == accepted_requests_strategy)
    {
        enable_flag(&state->events, found_accepted_requests_strategy_label);
    }
    else
    {
        enable_flag(&state->events, found_denied_requests_strategy_label);
    }

    state->target = target;
}

static inline void add_option_to_strategy(logging_policy_parser_state_t* state, logging_option_t option)
{
    if (state->target == accepted_requests_strategy)
    {
        enable_flag(&state->policy->accepted_requests_strategy, option);
    }
    else
    {
        enable_flag(&state->policy->denied_requests_strategy, option);
    }
}

logging_policy_parser_events_t parse_logging_policy_file(void* policy, FILE* file)
{
    logging_policy_parser_state_t state =
    {
        .line = 0,
        .policy = (logging_policy_t*) policy,
        .events = 0,
        .target = undefined_strategy
    };

    string_t* entry = string_from_size(ENTRY_SIZE);
    string_t* label = string_from_size(ENTRY_SIZE);

    while (1)
    {
        clear_contents_of(entry);
        clear_contents_of(label);

        if (fgets(entry->item, entry->capacity, file) == NULL)
        {
            break;
        }

        erase_whitespaces_from_string(entry, label);

        if (is_empty(label))
        {
            continue;
        }

        logging_policy_parser_target_t target = map_label_to_parser_target(label);

        if (target != undefined_strategy)
        {
            set_parser_target(&state, target);
            continue;
        }

        if (!has_target(&state))
        {
            continue;
        }

        logging_option_t option = map_label_to_strategy_option(label);

        if (option != unsupported_option)
        {
            add_option_to_strategy(&state, option);
            continue;
        }
    }

    dispose_string(entry);
    dispose_string(label);

    fclose(file);

    return state.events;
}