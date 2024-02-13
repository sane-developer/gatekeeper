#ifndef GATEKEEPER_BINDING_POLICY_PARSER_H
#define GATEKEEPER_BINDING_POLICY_PARSER_H

#include "../models/binding_policy.h"

///
/// @brief
///
struct binding_policy_parser_args_t;

///
/// @brief
///
struct binding_policy_parser_output_t;

///
/// @brief
///
struct binding_policy_validator_args_t;

///
/// @brief
/// @param args
/// @return
///
struct binding_policy_parser_output_t parse_binding_policy(const struct binding_policy_parser_args_t* args);

///
/// @brief
/// @param args
/// @return
///
int validate_binding_policy(const struct binding_policy_validator_args_t* args);

#endif