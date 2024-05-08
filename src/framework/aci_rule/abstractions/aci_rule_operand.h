#ifndef ACI_RULE_OPERAND_H
#define ACI_RULE_OPERAND_H

#include <nspr4/prio.h>

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
    uint32_t day_of_week;

    ///
    /// @brief
    ///
    uint32_t time_of_day;
}
aci_rule_operand_t;

#endif  // ACI_RULE_OPERAND_H
