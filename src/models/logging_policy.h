#ifndef GATEKEEPER_LOGGING_POLICY_H
#define GATEKEEPER_LOGGING_POLICY_H

///
/// @brief Represents the type of information that may be stored in logs while evaluating bind requests.
///
typedef enum
{
    ///
    /// @brief The value indicating that strategy option could not be resolved.
    ///
    unknown_strategy_option = -1,

    ///
    /// @brief The value indicating that logging should be entirely ignored.
    ///
    ignore_logging = 1 << 0,

    ///
    /// @brief The value indicating that rule label should be included in the log.
    ///
    include_rule_name = 1 << 1,

    ///
    /// @brief The value indicating that user dn should be included in the log.
    ///
    include_user_dn = 1 << 2,

    ///
    /// @brief The value indicating that user ip should be included in the log.
    ///
    include_user_ip = 1 << 3,

    ///
    /// @brief The value indicating that request evaluation should be included in the log.
    ///
    include_evaluation = 1 << 4,

    ///
    /// @brief The value indicating that date should be included in the log.
    ///
    include_date = 1 << 5,

    ///
    /// @brief The value indicating that authentication method should be included in the log.
    ///
    include_authentication_method = 1 << 6,

    ///
    /// @brief The value indicating that SASL method should be included in the log in case Kerberos has been used.
    ///
    include_sasl_method = 1 << 7
}
logging_strategy_t, logging_strategy_option_t;

///
/// @brief Represents the model of logging policy configuration.
///
typedef struct
{
    ///
    /// @brief The value indicating which request details should be logged for accepted requests.
    ///
    logging_strategy_t accepted_requests_strategy;

    ///
    /// @brief The value indicating which request details should be logged for denied requests.
    ///
    logging_strategy_t denied_requests_strategy;
}
logging_policy_t;

#endif