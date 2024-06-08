#include "aci_rule.h"
#include <string.h>

static bool all(const char* groups, const aci_rule_operands_t* operands)
{
    char* tokens = (char*) groups;

    for (size_t i = 0; i < OPERANDS_COUNT_LIMIT; ++i)
    {
        bool is_member_of_group = false;

        char* required_group = operands->items[i].group;

        char* actual_group;

        while ((actual_group = strtok_r(tokens, ",", &tokens)))
        {
            if (strcmp(actual_group, required_group) == 0)
            {
                is_member_of_group = true;

                break;
            }
        }

        if (!is_member_of_group)
        {
            return false;
        }
    }

    return true;
}

static bool any(const char* groups, const aci_rule_operands_t* operands)
{
    char* tokens = (char*) groups;

    for (size_t i = 0; i < OPERANDS_COUNT_LIMIT; ++i)
    {
        char* required_group = operands->items[i].group;

        char* actual_group;

        while ((actual_group = strtok_r(tokens, ",", &tokens)))
        {
            if (strcmp(actual_group, required_group) == 0)
            {
                return true;
            }
        }
    }

    return false;
}

bool has_satisfied_groups_operation(const char* groups, const aci_rule_operation_t* operation)
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
