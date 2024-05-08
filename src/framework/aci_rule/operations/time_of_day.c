#include "aci_rule_condition.h"

static bool after(const aci_rule_operands_t* operands, const PRExplodedTime* datetime)
{
    return 0;
}

static bool before(const aci_rule_operands_t* operands, const PRExplodedTime* datetime)
{
    return 0;
}

static bool between(const aci_rule_operands_t* operands, const PRExplodedTime* datetime)
{
    return 0;
}

time_of_day_operation get_time_of_day_operation(aci_rule_operation_t operation)
{
    switch (operation)
    {
        case AFTER:
            return after;
        case BEFORE:
            return before;
        case BETWEEN:
            return between;
        default:
            return NULL;
    }
}
