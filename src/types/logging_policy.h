#ifndef GATEKEEPER_LOGGING_POLICY_H
#define GATEKEEPER_LOGGING_POLICY_H

///
/// @brief Represents the type of information that may be stored in logs while evaluating bind requests.
///
typedef enum
{
    unsupported_option = -1,
    ignore_logging = 1 << 0,
    include_rule_name = 1 << 1,
    include_user_dn = 1 << 2,
    include_user_ip = 1 << 3,
    include_evaluation = 1 << 4,
    include_date = 1 << 5,
    include_authentication_method = 1 << 6,
    include_sasl_method = 1 << 7
}
logging_strategy_t, logging_option_t;

///
/// @brief Represents the model of logging policy configuration.
///
typedef struct
{
    logging_strategy_t accepted_requests_strategy;
    logging_strategy_t denied_requests_strategy;
}
logging_policy_t;

///
/// @brief Allocates the logging policy on the heap.
/// @return The pointer to newly allocated logging policy.
///
logging_policy_t* create_logging_policy();

///
/// @brief Disposes the allocated logging policy.
/// @param policy The pointer to the allocated logging policy.
///
void dispose_logging_policy(logging_policy_t* policy);

#endif