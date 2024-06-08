#include "aci_rule.h"
#include <dirsrv/slapi-plugin.h>
#include <string.h>

static bool matches(const char* dn, const aci_rule_operands_t* operands)
{
    char* pattern = operands->items[0].dn;

    Slapi_Regex* handler = slapi_re_comp(pattern, NULL);

    bool has_matched = slapi_re_exec_nt(handler, dn);

    slapi_re_free(handler);

    return has_matched;
}

static bool equals(const char* dn, const aci_rule_operands_t* operands)
{
    return strcmp(dn, operands->items[0].dn) == 0;
}

static bool starts_with(const char* dn, const aci_rule_operands_t* operands)
{
    char* target = operands->items[0].dn;

    size_t target_length = strlen(target);

    return strncmp(dn, target, target_length) == 0;
}

static bool ends_with(const char* dn, const aci_rule_operands_t* operands)
{
    char* target = operands->items[0].dn;

    size_t source_length = strlen(dn);

    size_t target_length = strlen(target);

    return strcmp(dn + source_length - target_length, target) == 0;
}

bool has_satisfied_dn_operation(const char* dn, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case MATCHES:
            return matches(dn, &operation->operands);
        case EQUALS:
            return equals(dn, &operation->operands);
        case STARTS_WITH:
            return starts_with(dn, &operation->operands);
        case ENDS_WITH:
            return ends_with(dn, &operation->operands);
        default:
            return false;
    }
}
