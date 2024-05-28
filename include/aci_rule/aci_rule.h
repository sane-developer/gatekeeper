#ifndef ACI_RULE_H
#define ACI_RULE_H

#include "aci_rule_condition.h"

#define CONDITIONS_LIMIT 5

typedef struct aci_rule_t
{
    char* label;

    aci_rule_condition_t exclude[CONDITIONS_LIMIT];

    aci_rule_condition_t apply[CONDITIONS_LIMIT];

    aci_rule_condition_t satisfy[CONDITIONS_LIMIT];

    struct aci_rule_t* next;
}
aci_rule_t, aci_rule_linked_list_t;

#endif  // ACI_RULE_H
