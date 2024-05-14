#ifndef ACI_RULE_OPERATION_TYPE_H
#define ACI_RULE_OPERATION_TYPE_H

///
/// @brief
///
typedef enum
{
    ///
    /// @brief
    ///
    MATCHES,

    ///
    /// @brief
    ///
    EQUALS,

    ///
    /// @brief
    ///
    RANGE,

    ///
    /// @brief
    ///
    AFTER,

    ///
    /// @brief
    ///
    BEFORE,

    ///
    /// @brief
    ///
    BETWEEN,

    ///
    /// @brief
    ///
    STARTS_WITH,

    ///
    /// @brief
    ///
    ENDS_WITH,

    ///
    /// @brief
    ///
    ANY_OF,

    ///
    /// @brief
    ///
    ALL_OF
}
aci_rule_operation_type_t;

#endif  // ACI_RULE_OPERATION_TYPE_H
