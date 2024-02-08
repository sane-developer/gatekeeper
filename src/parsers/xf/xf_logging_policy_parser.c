#include <stdio.h>
#include "xf_logging_policy_parser.h"
#include "../../loggers/logger.h"
#include "../../utilities/flags.h"
#include "../../utilities/string.h"

static inline xf_lpp_target_t map_label_to_parser_target(const string_t* label)
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
    log_warning("[Line %zu] [Out of scope] %s.", line, entry->item);
}

static inline void signal_unsupported_option(size_t line, const string_t* entry)
{
    log_warning("[Line %zu] [Unsupported] %s.", line, entry->item);
}

static inline void set_parser_target(xf_lpp_state_t* state, xf_lpp_target_t target)
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

static inline void add_option_to_strategy(logging_policy_t* policy, xf_lpp_target_t target, logging_option_t option)
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

xf_lpp_output_t parse_logging_policy(const xf_lpp_args_t* args)
{
    FILE* policy_file = fopen(args->path, "r");

    if (!policy_file)
    {
        return (xf_lpp_output_t)
        {
            .has_parsed = 0,
            .events = 0
        };
    }

    xf_lpp_state_t state =
    {
        .line = 0,
        .events = 0,
        .target = undefined_strategy
    };

    string_t* scattered = string_from_size(100);

    string_t* trimmed = string_from_size(100);

    while (1)
    {
        state.line++;
        
        remove_contents(scattered);

        remove_contents(trimmed);

        if (fgets(scattered->item, (int) scattered->size, policy_file) == NULL)
        {
            break;
        }

        erase_whitespaces_from_string(scattered, trimmed);

        if (is_empty(trimmed))
        {
            continue;
        }

        const xf_lpp_target_t target = map_label_to_parser_target(trimmed);

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
            add_option_to_strategy(args->policy, state.target, option);
            continue;
        }

        signal_unsupported_option(state.line, trimmed);
    }

    dispose_string(scattered);

    dispose_string(trimmed);

    fclose(policy_file);

    return (xf_lpp_output_t)
    {
        .has_parsed = 1,
        .events = state.events
    };
}

char validate_logging_policy(const xf_lpv_args_t* args)
{
    char is_valid = 1;

    if (!has_flag(args->events, found_accepted_requests_strategy_label))
    {
        log_critical("[Not found] Accepted requests strategy configuration.");
        is_valid = 0;
    }

    if (!has_flag(args->events, found_denied_requests_strategy_label))
    {
        log_critical("[Not found] Denied requests strategy configuration.");
        is_valid = 0;
    }

    if (args->policy->accepted_requests_strategy == uninitialized_strategy)
    {
        log_critical("[Unassigned] Accepted requests strategy configuration.");
        is_valid = 0;
    }

    if (args->policy->denied_requests_strategy == uninitialized_strategy)
    {
        log_critical("[Unassigned] Denied requests strategy configuration.");
        is_valid = 0;
    }

    return is_valid;
}