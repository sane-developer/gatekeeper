#include "aci_rule_conditions.h"

static bool after(const aci_rule_condition_operands_t* operands, const PRExplodedTime* datetime)
{
    return 0;
}

static bool before(const aci_rule_condition_operands_t* operands, const PRExplodedTime* datetime)
{
    return 0;
}

static bool between(const aci_rule_condition_operands_t* operands, const PRExplodedTime* datetime)
{
    return 0;
}

bool satisfies_day_of_week_condition(const aci_rule_condition_t* condition, const PRExplodedTime* datetime)
{
    switch (condition->operation)
    {
        case AFTER:
            return after(condition->operands, datetime);
        case BEFORE:
            return before(condition->operands, datetime);
        case BETWEEN:
            return between(condition->operands, datetime);
        default:
            return false;
    }
}
