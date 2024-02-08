#ifndef GATEKEEPER_LOGGING_POLICY_PARSER_H
#define GATEKEEPER_LOGGING_POLICY_PARSER_H

#include "../models/logging_policy.h"

///
/// @brief
///
struct logging_policy_parser_args_t;

///
/// @brief
///
struct logging_policy_parser_output_t;

///
/// @brief
///
struct logging_policy_validator_args_t;

///
/// @brief
/// @param args
/// @return
///
struct logging_policy_parser_output_t parse_logging_policy(const struct logging_policy_parser_args_t* args);

///
/// @brief
/// @param args
/// @return
///
char validate_logging_policy(const struct logging_policy_validator_args_t* args);

#endif