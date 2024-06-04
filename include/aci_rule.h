#ifndef ACI_RULE_H
#define ACI_RULE_H

#include <nspr4/prio.h>

///
/// @brief
///
#define RULES_LIMIT 10

///
/// @brief
///
#define CONDITIONS_LIMIT 5

///
/// @brief
///
#define OPERATIONS_LIMIT 5

///
/// @brief
///
#define OPERANDS_LIMIT 5

///
/// @brief
///
#define RULE_LABEL_LENGTH_LIMIT 256

///
/// @brief
///
#define CONDITION_LABEL_LENGTH_LIMIT 256

///
/// @brief
///
typedef union
{
    char* dn;

    char* group;

    PRNetAddr* ip;

    PRNetAddr* dns;

    uint32_t time;

    uint32_t weekday;
}
aci_rule_operand_t;

///
/// @brief
///
typedef enum
{
    DN,

    GROUP,

    IP,

    DNS,

    TIME,

    WEEKDAY
}
aci_rule_operand_type_t;

///
/// @brief
///
typedef enum
{
    ALL,

    ANY,

    AFTER,

    BEFORE,

    BETWEEN,

    ENDS_WITH,

    EQUALS,

    MATCHES,

    STARTS_WITH,

    RANGE
}
aci_rule_operation_type_t;

///
/// @brief
///
typedef enum
{
    NOP,

    AND,

    OR
}
aci_rule_operator_type_t;

///
/// @brief
///
typedef struct
{
    aci_rule_operation_type_t operation_type;

    aci_rule_operator_type_t operator_type;

    aci_rule_operand_type_t operand_type;

    aci_rule_operand_t operands[OPERANDS_LIMIT];
}
aci_rule_operation_t;

///
/// @brief
///
typedef struct
{
    char label[CONDITION_LABEL_LENGTH_LIMIT];

    aci_rule_operation_t operations[OPERATIONS_LIMIT];
}
aci_rule_condition_t;

///
/// @brief
///
typedef struct
{
    char label[RULE_LABEL_LENGTH_LIMIT];

    aci_rule_condition_t exclude[CONDITIONS_LIMIT];

    aci_rule_condition_t apply[CONDITIONS_LIMIT];

    aci_rule_condition_t satisfy[CONDITIONS_LIMIT];
}
aci_rule_t;

#endif  // ACI_RULE_H
