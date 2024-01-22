#ifndef GATEKEEPER_LOGGING_POLICY_PARSER_H
#define GATEKEEPER_LOGGING_POLICY_PARSER_H

#include <stdio.h>
#include "../types/logging_policy.h"

///
/// @brief Represents the targets which may occur while parsing the logging policy file.
///
typedef enum
{
    undefined_strategy,
    accepted_requests_strategy,
    denied_requests_strategy
}
logging_policy_parser_target_t;

///
/// @brief Represents the events which may occur while parsing the logging policy file.
///
typedef enum
{
    found_accepted_requests_strategy_label = 1 << 0,
    found_denied_requests_strategy_label = 1 << 1
}
logging_policy_parser_events_t;

///
/// @brief Represents the output of parsing the logging policy file.
///
typedef struct
{
    size_t line;
    logging_policy_t* policy;
    logging_policy_parser_events_t events;
    logging_policy_parser_target_t target;
}
logging_policy_parser_state_t;

///
/// @brief Parses the specified logging policy file.
/// @param policy The pointer to the logging policy to populate.
/// @param file The pointer to the file handle containing the logging policy definition.
/// @return The flags indicating events which occurred during the parsing routine.
/// @remark The file will be closed after parsing.
///
logging_policy_parser_events_t parse_logging_policy_file(void* policy, FILE* file);

#endif