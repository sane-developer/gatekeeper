#include <stdio.h>
#include "../logging_policy_parser.h"
#include "../../loggers/logger.h"
#include "../../utilities/flags.h"
#include "../../utilities/string.h"

typedef enum
{
    found_accepted_requests_strategy_label = 1 << 0,
    found_denied_requests_strategy_label = 1 << 1
}
parser_events_t;

typedef enum
{
    undefined_strategy,
    accepted_requests_strategy,
    denied_requests_strategy
}
parser_target_t;

typedef struct
{
    size_t line;
    parser_events_t events;
    parser_target_t target;
}
parser_state_t;

static inline parser_target_t map_label_to_parser_target(const string_t* label)
{
    if (matches_string_literal(label, "accepted_requests_strategy"))
    {
        return accepted_requests_strategy;
    }

    if (matches_string_literal(label, "denied_requests_strategy"))
    {
        return denied_requests_strategy;
    }

    return undefined_strategy;
}

static inline logging_option_t map_label_to_strategy_option(const string_t* label)
{
    if (matches_string_literal(label, "ignore_logging"))
    {
        return ignore_logging;
    }

    if (matches_string_literal(label, "include_rule_name"))
    {
        return include_rule_name;
    }

    if (matches_string_literal(label, "include_user_dn"))
    {
        return include_user_dn;
    }

    if (matches_string_literal(label, "include_user_ip"))
    {
        return include_user_ip;
    }

    if (matches_string_literal(label, "include_evaluation"))
    {
        return include_evaluation;
    }

    if (matches_string_literal(label, "include_date"))
    {
        return include_date;
    }

    if (matches_string_literal(label, "include_authentication_method"))
    {
        return include_authentication_method;
    }

    if (matches_string_literal(label, "include_sasl_method"))
    {
        return include_sasl_method;
    }

    return unsupported_option;
}

static inline void signal_out_of_scope_entry(size_t line, const string_t* entry)
{
    log_info("Found entry outside any strategy declaration scope at line %zu [%s].", line, entry->item);
}

static inline void signal_unsupported_option(size_t line, const string_t* entry)
{
    log_info("Found unsupported option declaration at line %zu [%s].", line, entry->item);
}

static inline void signal_critical_issues(parser_events_t events)
{
    if (!has_flag(events, found_accepted_requests_strategy_label))
    {
        log_critical("Could not find accepted requests strategy configuration.");
    }

    if (!has_flag(events, found_denied_requests_strategy_label))
    {
        log_critical("Could not find denied requests strategy configuration.");
    }
}

static inline void set_parser_target(parser_state_t* state, parser_target_t target)
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

static inline void add_option_to_strategy(logging_policy_t* policy, parser_target_t target, logging_option_t option)
{
    if (target == accepted_requests_strategy)
    {
        enable_flag(&policy->accepted_requests_strategy, option);
    }
    else
    {
        enable_flag(&policy->denied_requests_strategy, option);
    }
}

logging_policy_t* parse_logging_policy(void* resource)
{
    FILE* file = (FILE*) resource;

    logging_policy_t* policy = create_logging_policy();

    parser_state_t state =
    {
        .line = 0,
        .events = 0,
        .target = undefined_strategy
    };

    const size_t entry_length = 100;

    string_t* scattered = string_from_size(entry_length);

    string_t* trimmed = string_from_size(entry_length);

    while (1)
    {
        remove_contents(scattered);

        remove_contents(trimmed);

        if (fgets(scattered->item, scattered->size, file) == NULL)
        {
            break;
        }

        erase_whitespaces_from_string(scattered, trimmed);

        if (is_empty(trimmed))
        {
            continue;
        }

        const parser_target_t target = map_label_to_parser_target(trimmed);

        if (target != undefined_strategy)
        {
            set_parser_target(&state, target);
            continue;
        }

        if (state.target == undefined_strategy)
        {
            signal_out_of_scope_entry(state.line, trimmed);
            continue;
        }

        const logging_option_t option = map_label_to_strategy_option(trimmed);

        if (option != unsupported_option)
        {
            add_option_to_strategy(policy, state.target, option);
            continue;
        }

        signal_unsupported_option(state.line, trimmed);
    }

    dispose_string(scattered);

    dispose_string(trimmed);

    signal_critical_issues(state.events);

    fclose(file);

    return policy;
}