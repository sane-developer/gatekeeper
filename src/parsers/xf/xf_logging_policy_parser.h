#ifndef GATEKEEPER_XF_LOGGING_POLICY_PARSER_H
#define GATEKEEPER_XF_LOGGING_POLICY_PARSER_H

#include <stddef.h>
#include "../logging_policy_parser.h"
#include "../../models/logging_policy.h"

typedef enum
{
    failed_to_allocate_logging_policy = 1 << 0,
    failed_to_open_logging_policy_file = 1 << 1,
    failed_to_locate_ars_label = 1 << 2,
    failed_to_locate_drs_label = 1 << 3
}
xf_lpp_errors_t;

typedef enum
{
    undefined_strategy,
    accepted_requests_strategy,
    denied_requests_strategy
}
xf_lpp_target_t;

typedef struct
{
    size_t line;
    xf_lpp_errors_t errors;
    xf_lpp_target_t target;
}
xf_lpp_state_t;

typedef struct logging_policy_parser_args_t
{
    char* path;
}
xf_lpp_args_t;

typedef struct logging_policy_parser_output_t
{
    xf_lpp_errors_t errors;
    logging_policy_t* policy;
}
xf_lpp_output_t;

typedef struct logging_policy_validator_args_t
{
    xf_lpp_errors_t errors;
    logging_policy_t* policy;
}
xf_lpv_args_t;

#endif