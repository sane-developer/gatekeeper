#ifndef ACI_RULE_OPERAND_H
#define ACI_RULE_OPERAND_H

#include <nspr4/prio.h>

///
/// @brief
///
#define MAX_OPERANDS_COUNT 5

///
/// @brief
///
typedef union
{
    ///
    /// @brief
    ///
    char* dn;

    ///
    /// @brief
    ///
    PRNetAddr* ip;

    ///
    /// @brief
    ///
    PRNetAddr* dns;

    ///
    /// @brief
    ///
    char* role;

    ///
    /// @brief
    ///
    char* group;

    ///
    /// @brief
    ///
    char* attribute;

    ///
    /// @brief
    ///
    uint32_t weekday;

    ///
    /// @brief
    ///
    uint32_t time;
}
aci_rule_operand_value_t;

#endif  // ACI_RULE_OPERAND_H
