#include "logging_policy_validator.h"
#include "../loggers/logger.h"

char validate_logging_policy(const logging_policy_t* policy)
{
    char is_valid = 1;

    if (policy->accepted_requests_strategy == uninitialized_strategy)
    {
        log_critical("The accepted requests strategy has not been assigned any value.");
        is_valid = 0;
    }

    if (policy->denied_requests_strategy == uninitialized_strategy)
    {
        log_critical("The denied requests strategy has not been assigned any value.");
        is_valid = 0;
    }

    return is_valid;
}