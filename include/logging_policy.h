#ifndef GATEKEEPER_LOGGING_POLICY_H
#define GATEKEEPER_LOGGING_POLICY_H

///
/// @brief Represents a set of flags which define information contained in logs.
///
typedef enum
{
    uninitialized_strategy = 1 << 0,
    unsupported_strategy_option = 1 << 1,
    include_user_dn = 1 << 2,
    include_user_ip = 1 << 3,
    include_user_group = 1 << 4,
    include_user_role = 1 << 5,
    include_evaluation = 1 << 6,
    include_date = 1 << 7,
    include_authentication_method = 1 << 8,
    include_sasl_method = 1 << 9,
}
logging_strategy_t, logging_strategy_option_t;

///
/// @brief Represents a policy defining the logging behavior of the plugin.
///
typedef struct
{
    logging_strategy_t accepted_requests;
    logging_strategy_t denied_requests;
}
logging_policy_t;

#endif //GATEKEEPER_LOGGING_POLICY_H
