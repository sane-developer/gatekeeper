#include "aci_rule.h"
#include <string.h>

static bool all(char** groups, const aci_rule_operands_t* operands)
{
    for (size_t i = 0; i < operands->count; ++i)
    {
        bool is_member = false;

        for (size_t j = 0; groups[j]; ++j)
        {
            if (strcmp(operands->items[i].text, groups[j]) == 0)
            {
                is_member = true;

                break;
            }
        }

        if (!is_member)
        {
            return false;
        }
    }

    return true;
}

static bool any(char** groups, const aci_rule_operands_t* operands)
{
    for (size_t i = 0; i < operands->count; ++i)
    {
        for (size_t j = 0; groups[j]; ++j)
        {
            if (strcmp(operands->items[i].text, groups[j]) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool has_satisfied_groups_operation(char** groups, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case ALL:
            return all(groups, &operation->operands);
        case ANY:
            return any(groups, &operation->operands);
        default:
            return false;
    }
}
