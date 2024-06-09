#include "aci_rule.h"

static bool after(uint32_t weekday, const aci_rule_operands_t* operands)
{
    return operands->items[0].integer < weekday;
}

static bool before(uint32_t weekday, const aci_rule_operands_t* operands)
{
    return operands->items[0].integer > weekday;
}

static bool between(uint32_t weekday, const aci_rule_operands_t* operands)
{
    return operands->items[0].integer <= weekday && weekday <= operands->items[1].integer;
}

static bool equals(uint32_t weekday, const aci_rule_operands_t* operands)
{
    return operands->items[0].integer == weekday;
}

bool has_satisfied_weekday_operation(uint32_t weekday, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case AFTER:
            return after(weekday, &operation->operands);
        case BEFORE:
            return before(weekday, &operation->operands);
        case BETWEEN:
            return between(weekday, &operation->operands);
        case EQUALS:
            return equals(weekday, &operation->operands);
        default:
            return false;
    }
}
