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
        disable_flag(&state->errors, failed_to_locate_ars_label);
    }
    else
    {
        disable_flag(&state->errors, failed_to_locate_drs_label);
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
    logging_policy_t* policy = create_logging_policy();

    if (!policy)
    {
        return (xf_lpp_output_t)
        {
            .errors = failed_to_allocate_logging_policy,
            .policy = NULL
        };
    }

    FILE* policy_file = fopen(args->path, "r");

    if (!policy_file)
    {
        dispose_logging_policy(policy);

        return (xf_lpp_output_t)
        {
            .errors = failed_to_open_logging_policy_file,
            .policy = NULL
        };
    }

    xf_lpp_state_t state =
    {
        .line = 0,
        .errors = failed_to_locate_ars_label | failed_to_locate_drs_label,
        .target = undefined_strategy
    };

    string_t* raw = string_from_size(100);

    string_t* label = string_from_size(100);

    while (1)
    {
        state.line++;
        
        remove_contents(raw);

        remove_contents(label);

        if (fgets(raw->item, (int) raw->size, policy_file) == NULL)
        {
            break;
        }

        erase_whitespaces_from_string(raw, label);

        if (is_empty(label))
        {
            continue;
        }

        const xf_lpp_target_t target = map_label_to_parser_target(label);

        if (target != undefined_strategy)
        {
            set_parser_target(&state, target);
            continue;
        }

        if (state.target == undefined_strategy)
        {
            signal_out_of_scope_entry(state.line, label);
            continue;
        }

        const logging_option_t option = map_label_to_strategy_option(label);

        if (option != unsupported_option)
        {
            add_option_to_strategy(policy, state.target, option);
            continue;
        }

        signal_unsupported_option(state.line, label);
    }

    dispose_string(raw);

    dispose_string(label);

    fclose(policy_file);

    return (xf_lpp_output_t)
    {
        .errors = state.errors,
        .policy = policy
    };
}

int validate_logging_policy(const xf_lpv_args_t* args)
{
    char is_valid = 1;

    if (has_flag(args->errors, failed_to_allocate_logging_policy))
    {
        log_critical("Unable to allocate the logging policy structure.");
        return 1;
    }

    if (has_flag(args->errors, failed_to_open_logging_policy_file))
    {
        log_critical("Unable to open the policy configuration file.");
        return 1;
    }

    if (has_flag(args->errors, failed_to_locate_ars_label))
    {
        log_critical("[Not found] Accepted requests strategy configuration.");
        is_valid = 0;
    }

    if (has_flag(args->errors, failed_to_locate_drs_label))
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