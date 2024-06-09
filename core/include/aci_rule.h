#ifndef ACI_RULE_H
#define ACI_RULE_H

#include <nspr4/prio.h>
#include <stdbool.h>

///
/// @brief
///
#define RULES_COUNT_LIMIT 10

///
/// @brief
///
#define CONDITIONS_COUNT_LIMIT 5

///
/// @brief
///
#define OPERATIONS_COUNT_LIMIT 5

///
/// @brief
///
#define OPERANDS_COUNT_LIMIT 5

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

    STARTS_WITH
}
aci_rule_operation_type_t;

///
/// @brief
///
typedef enum
{
    AND,

    OR,

    NOP
}
aci_rule_operator_type_t;

///
/// @brief
///
typedef enum
{
    DN,

    GROUPS,

    IP,

    DNS,

    TIME,

    WEEKDAY
}
aci_rule_operand_type_t;

///
/// @brief
///
typedef union
{
    char* text;

    uint32_t integer;
}
aci_rule_operand_t;

///
/// @brief
///
typedef struct
{
    aci_rule_operand_t items[OPERANDS_COUNT_LIMIT];

    size_t count;
}
aci_rule_operands_t;

///
/// @brief
///
typedef struct
{
    aci_rule_operation_type_t operation_type;

    aci_rule_operator_type_t operator_type;

    aci_rule_operand_type_t operand_type;

    aci_rule_operands_t operands;
}
aci_rule_operation_t;

///
/// @brief
///
typedef struct
{
    aci_rule_operation_t items[OPERATIONS_COUNT_LIMIT];

    size_t count;
}
aci_rule_operations_t;

///
/// @brief
///
typedef struct
{
    char label[CONDITION_LABEL_LENGTH_LIMIT];

    aci_rule_operations_t operations;
}
aci_rule_condition_t;

///
/// @brief
///
typedef struct
{
    aci_rule_condition_t items[CONDITIONS_COUNT_LIMIT];

    size_t count;
}
aci_rule_conditions_t;

///
/// @brief
///
typedef struct
{
    char label[RULE_LABEL_LENGTH_LIMIT];

    aci_rule_conditions_t exclude;

    aci_rule_conditions_t apply;

    aci_rule_conditions_t trigger;
}
aci_rule_t;

///
/// @brief
///
typedef struct
{
    aci_rule_t items[RULES_COUNT_LIMIT];

    size_t count;
}
aci_rules_t;

///
/// @brief
/// @param dn
/// @param operation
/// @return
///
bool has_satisfied_dn_operation(const char* dn, const aci_rule_operation_t* operation);

///
/// @brief
/// @param dn
/// @param operation
/// @return
///
bool has_satisfied_groups_operation(const char* groups, const aci_rule_operation_t* operation);

///
/// @brief
/// @param dn
/// @param operation
/// @return
///
bool has_satisfied_ip_operation(const PRNetAddr* ip, const aci_rule_operation_t* operation);

///
/// @brief
/// @param dn
/// @param operation
/// @return
///
bool has_satisfied_dns_operation(const PRNetAddr* dns, const aci_rule_operation_t* operation);

///
/// @brief
/// @param dn
/// @param operation
/// @return
///
bool has_satisfied_time_operation(const uint32_t time, const aci_rule_operation_t* operation);

///
/// @brief
/// @param dn
/// @param operation
/// @return
///
bool has_satisfied_weekday_operation(const uint32_t weekday, const aci_rule_operation_t* operation);

#endif  // ACI_RULE_H
