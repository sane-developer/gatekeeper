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
    int day_of_week;

    ///
    /// @brief
    ///
    struct { int hours; int minutes; } time_of_day;
}
aci_rule_operand_t;


///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    aci_rule_operand_t* items;

    ///
    /// @brief
    ///
    size_t capacity;

    ///
    /// @brief
    ///
    size_t count;
}
aci_rule_operands_t;

#endif  // ACI_RULE_OPERAND_H
