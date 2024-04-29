#ifndef ACI_RULE_CONDITION_OPERATION_H_
#define ACI_RULE_CONDITION_OPERATION_H_

///
/// @brief Represents the supported operations for ACI rule conditions.
///
typedef enum
{
    ///
    /// @brief
    ///
    MATCHES = 1 << 0,

    ///
    /// @brief
    ///
    EQUALS = 1 << 1,
}
aci_rule_condition_operation_t;

#endif  // ACI_RULE_CONDITION_OPERATION_H_
