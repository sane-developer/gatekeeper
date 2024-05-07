#include "aci_rule_condition.h"
#include <string.h>
#include <regex.h>

static bool equals(const aci_rule_operands_t* operands, const char* source)
{
    const char* target = operands->items[0].dn;

    return strcmp(source, target) == 0;
}

static bool matches(const aci_rule_operands_t* operands, const char* source)
{
    const char* target = operands->items[0].dn;

    regex_t expression = {0};

    return regcomp(&expression, target, 0) && regexec(&expression, source, 0, NULL, 0) == 0;
}

static bool starts_with(const aci_rule_operands_t* operands, const char* source)
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

static bool ends_with(const aci_rule_operands_t* operands, const char* source)
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

static bool in(const aci_rule_operands_t* operands, const char* source)
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

dn_operation get_dn_operation(aci_rule_operation_t operation)
{
    switch (operation)
    {
        case EQUALS:
            return equals;
        case MATCHES:
            return matches;
        case STARTS_WITH:
            return starts_with;
        case ENDS_WITH:
            return ends_with;
        case IN:
            return in;
        default:
            return NULL;
    }
}
