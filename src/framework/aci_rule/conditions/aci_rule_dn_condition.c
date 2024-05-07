#include <string.h>
#include <regex.h>
#include "aci_rule_conditions.h"

static bool equals(const aci_rule_condition_operands_t* operands, const char* source)
{
    const char* target = operands->items[0].dn;

    return strcmp(source, target) == 0;
}

static bool matches(const aci_rule_condition_operands_t* operands, const char* source)
{
    const char* target = operands->items[0].dn;

    regex_t expression = {0};

    return regcomp(&expression, target, 0) && regexec(&expression, source, 0, NULL, 0) == 0;
}

static bool starts_with(const aci_rule_condition_operands_t* operands, const char* source)
{
    const char* target = operands->items[0].dn;

    for (size_t i = 0; i < strlen(target); ++i)
    {
        if (source[i] != target[i])
        {
            return false;
        }
    }

    return true;
}

static bool ends_with(const aci_rule_condition_operands_t* operands, const char* source)
{
    const char* target = operands->items[0].dn;

    const int source_last_letter_index = strlen(source) - 1;

    const int target_last_letter_index = strlen(target) - 1;

    const int offset = source_last_letter_index - target_last_letter_index;

    if (offset < 0)
    {
        return false;
    }

    for (size_t i = source_last_letter_index; i > target_last_letter_index; --i)
    {
        if (source[i] != target[i - offset])
        {
            return false;
        }
    }

    return true;
}

static bool in(const aci_rule_condition_operands_t* operands, const char* source)
{
    for (size_t i = 0; i < operands->count; ++i)
    {
        const char* target = operands->items[i].dn;

        if (strcmp(source, target) == 0)
        {
            return true;
        }
    }

    return false;
}

bool satisfies_dn_condition(const aci_rule_condition_t* condition, const char* dn)
{
    switch (condition->operation)
    {
        case EQUALS:
            return equals(condition->operands, dn);
        case MATCHES:
            return matches(condition->operands, dn);
        case STARTS_WITH:
            return starts_with(condition->operands, dn);
        case ENDS_WITH:
            return ends_with(condition->operands, dn);
        case IN:
            return in(condition->operands, dn);
        default:
            return false;
    }
}
