#ifndef GATEKEEPER_XF_LOGGING_POLICY_PARSER_H
#define GATEKEEPER_XF_LOGGING_POLICY_PARSER_H

#include <stddef.h>
#include "../logging_policy_parser.h"
#include "../../models/logging_policy.h"

typedef enum
{
    found_accepted_requests_strategy_label = 1 << 0,
    found_denied_requests_strategy_label = 1 << 1
}
xf_lpp_events_t;

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
    xf_lpp_events_t events;
    xf_lpp_target_t target;
}
xf_lpp_state_t;

typedef struct logging_policy_parser_args_t
{
    char* path;
    logging_policy_t* policy;
}
xf_lpp_args_t;

typedef struct logging_policy_parser_output_t
{
    char has_parsed;
    xf_lpp_events_t events;
}
xf_lpp_output_t;

typedef struct logging_policy_validator_args_t
{
    xf_lpp_events_t events;
    logging_policy_t* policy;
}
xf_lpv_args_t;

#endif