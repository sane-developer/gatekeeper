#ifndef ACI_RULE_CONDITION_H
#define ACI_RULE_CONDITION_H

#include "aci_rule_operation.h"

#define OPERATIONS_LIMIT 5

typedef struct
{
    char* label;

    aci_rule_operation_t operations[OPERATIONS_LIMIT];
}
aci_rule_condition_t;

#endif  // ACI_RULE_CONDITION_H
