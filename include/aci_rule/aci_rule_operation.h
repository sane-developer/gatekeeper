#ifndef ACI_RULE_OPERATION_H
#define ACI_RULE_OPERATION_H

#include <nspr4/prio.h>

#define OPERANDS_LIMIT 5

typedef enum
{
    DN,

    IP,

    DNS,

    GROUP,

    ATTRIBUTE,

    WEEKDAY,

    TIME
}
aci_rule_operand_type_t;

typedef enum
{
    MATCHES,

    EQUALS,

    RANGE,

    AFTER,

    BEFORE,

    BETWEEN,

    STARTS_WITH,

    ENDS_WITH,

    ANY_OF,

    ALL_OF
}
aci_rule_operation_type_t;

typedef enum
{
    AND,

    OR,

    TERMINATE
}
aci_rule_operator_type_t;

typedef union
{
    char* dn;

    PRNetAddr* ip;

    PRNetAddr* dns;

    char* group;

    char* attribute;

    uint32_t weekday;

    uint32_t time;
}
aci_rule_operand_t;

typedef struct
{
    aci_rule_operand_t operands[OPERANDS_LIMIT];

    aci_rule_operand_type_t operand_type;

    aci_rule_operation_type_t operation_type;

    aci_rule_operator_type_t operator_type;
}
aci_rule_operation_t;

#endif  // ACI_RULE_OPERATION_H
