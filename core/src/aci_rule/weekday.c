#include "aci_rule.h"

static bool after(uint32_t weekday, const aci_rule_operands_t* operands)
{
    return operands->items[0].weekday < weekday;
}

static bool before(uint32_t weekday, const aci_rule_operands_t* operands)
{
    return operands->items[0].weekday > weekday;
}

static bool between(uint32_t weekday, const aci_rule_operands_t* operands)
{
    return operands->items[0].weekday <= weekday <= operands->items[1].weekday;
}

static bool equals(uint32_t weekday, const aci_rule_operands_t* operands)
{
    return operands->items[0].weekday == weekday;
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
