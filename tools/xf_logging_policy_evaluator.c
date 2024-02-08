#include <assert.h>
#include "../src/loggers/logger.h"
#include "../src/parsers/xf/xf_logging_policy_parser.h"
#include "../src/utilities/flags.h"

static inline void report_strategy_options(const char* header, logging_strategy_t strategy)
{
    log_info("\n\n%s contains:\n", header);

    if (has_flag(strategy, include_rule_name))
    {
        log_info("include_rule_name");
    }

    if (has_flag(strategy, include_user_dn))
    {
        log_info("include_user_dn");
    }

    if (has_flag(strategy, include_user_ip))
    {
        log_info("include_user_ip");
    }

    if (has_flag(strategy, include_evaluation))
    {
        log_info("include_evaluation");
    }

    if (has_flag(strategy, include_date))
    {
        log_info("include_date");
    }

    if (has_flag(strategy, include_authentication_method))
    {
        log_info("include_authentication_method");
    }

    if (has_flag(strategy, include_sasl_method))
    {
        log_info("include_sasl_method");
    }
}

int main(int argc, char** argv)
{
    assert(argc > 0 && "Path to policy file has not been provided.");

    char* path = argv[1];

    assert(path && "Path to policy file was NULL.");

    logging_policy_t* policy = create_logging_policy();

    xf_lpp_args_t parser_args =
    {
        .path = path,
        .policy = policy,
    };

    xf_lpp_output_t output = parse_logging_policy(&parser_args);

    if (!output.has_parsed)
    {
        log_critical("Unable to open the policy configuration file.");
        return 1;
    }

    xf_lpv_args_t validator_args =
    {
        .events = output.events,
        .policy = policy,
    };

    char is_valid = validate_logging_policy(&validator_args);

    if (is_valid)
    {
        report_strategy_options("accepted_requests_strategy", policy->accepted_requests_strategy);

        report_strategy_options("denied_requests_strategy", policy->denied_requests_strategy);

        log_info("\nFile contains valid logging policy based on xf standard.");
    }
    else
    {
        log_critical("\nFile contains invalid logging policy based on xf standard.");
    }

    dispose_logging_policy(policy);
}
