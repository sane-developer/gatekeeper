#include <assert.h>
#include <stdio.h>
#include "../src/loggers/logger.h"
#include "../src/parsers/logging_policy_parser.h"
#include "../src/utilities/flags.h"
#include "../src/validators/logging_policy_validator.h"

static inline FILE* get_policy_file(int argc, char** argv)
{
//    assert(argc > 0 && "Path to policy file has not been provided.");
//
//    const char* path = argv[1];
//
//    assert(path && "Path to policy file was NULL.");

    FILE* file = fopen("./test.conf", "r");

    assert(file && "Could not open the file at specified path.");

    return file;
}

static inline void report_strategy_options(const char* header, logging_strategy_t strategy)
{
    log_info("%s contains:", header);

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
    FILE* policy_file = get_policy_file(argc, argv);

    logging_policy_t* policy = parse_logging_policy(policy_file);

    char is_valid = validate_logging_policy(policy);

    if (is_valid)
    {
        report_strategy_options("accepted_requests_strategy", policy->accepted_requests_strategy);

        report_strategy_options("denied_requests_strategy", policy->denied_requests_strategy);

        log_info("File contains valid logging policy based on xf standard.");
    }
    else
    {
        log_critical("File contains invalid logging policy based on xf standard.");
    }

    dispose_logging_policy(policy);
}