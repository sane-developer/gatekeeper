#include "aci_rule.h"

static bool after(uint32_t time, const aci_rule_operands_t* operands)
{
    return operands->items[0].time < time;
}

static bool before(uint32_t time, const aci_rule_operands_t* operands)
{
    return operands->items[0].time > time;
}

static bool between(uint32_t time, const aci_rule_operands_t* operands)
{
    return operands->items[0].time <= time <= operands->items[1].time;
}

bool has_satisfied_time_operation(uint32_t time, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case AFTER:
            return after(time, &operation->operands);
        case BEFORE:
            return before(time, &operation->operands);
        case BETWEEN:
            return between(time, &operation->operands);
        default:
            return false;
    }
}
