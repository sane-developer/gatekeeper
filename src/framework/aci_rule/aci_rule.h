#ifndef GATEKEEPER_ACI_RULE_T_H
#define GATEKEEPER_ACI_RULE_T_H

#include <nspr4/prio.h>

typedef enum aci_rule_condition_operation_flags_t
{
    IN = 1 << 0,

    ANY = 1 << 1,

    ALL = 1 << 2,

    HAS = 1 << 3,

    RANGE = 1 << 4,

    AFTER = 1 << 5,

    BEFORE = 1 << 6,

    BETWEEN = 1 << 7,

    EQUALS = 1 << 8,

    MATCHES = 1 << 9,

    STARTS_WITH = 1 << 10,

    ENDS_WITH = 1 << 11
}
aci_rule_condition_operation_t;

typedef enum aci_rule_condition_parameters_t
{
    DN,

    IP,

    DNS,

    ROLES,

    GROUPS,

    ATTRIBUTES,

    DAY_OF_WEEK,

    TIME_OF_DAY
}
aci_rule_condition_parameter_t;

typedef union
{
    char* dn;

    PRNetAddr* ip;

    PRNetAddr* dns;

    char* role;

    char* group;

    char* attribute;

    int day_of_week;

    struct { int hours; int minutes; } time_of_day;
}
aci_rule_condition_operand_t;

typedef struct
{
    aci_rule_condition_operand_t* items;

    size_t capacity;

    size_t count;
}
aci_rule_condition_operands_t;

typedef struct
{
    aci_rule_condition_parameter_t parameter;

    aci_rule_condition_operation_t operation;

    aci_rule_condition_operands_t* operands;
}
aci_rule_condition_t;

typedef struct
{
    aci_rule_condition_t** items;

    size_t capacity;

    size_t count;
}
aci_rule_conditions_t;

typedef struct
{
    char* label;

    aci_rule_conditions_t* exclude;

    aci_rule_conditions_t* apply;

    aci_rule_conditions_t* bind;
}
aci_rule_t;

typedef struct
{
    aci_rule_t** items;

    size_t capacity;

    size_t count;
}
aci_rules_t;

#endif  // GATEKEEPER_ACI_RULE_T_H
