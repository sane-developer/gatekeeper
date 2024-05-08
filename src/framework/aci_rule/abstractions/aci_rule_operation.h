#ifndef ACI_RULE_OPERATION_H
#define ACI_RULE_OPERATION_H

///
/// @brief
///
typedef enum
{
    ///
    /// @brief
    ///
    IN = 1 << 0,

    ///
    /// @brief
    ///
    ANY = 1 << 1,

    ///
    /// @brief
    ///
    ALL = 1 << 2,

    ///
    /// @brief
    ///
    HAS = 1 << 3,

    ///
    /// @brief
    ///
    RANGE = 1 << 4,

    ///
    /// @brief
    ///
    AFTER = 1 << 5,

    ///
    /// @brief
    ///
    BEFORE = 1 << 6,

    ///
    /// @brief
    ///
    BETWEEN = 1 << 7,

    ///
    /// @brief
    ///
    EQUALS = 1 << 8,

    ///
    /// @brief
    ///
    MATCHES = 1 << 9,

    ///
    /// @brief
    ///
    STARTS_WITH = 1 << 10,

    ///
    /// @brief
    ///
    ENDS_WITH = 1 << 11
}
aci_rule_operation_t;

#endif  // ACI_RULE_OPERATION_H
