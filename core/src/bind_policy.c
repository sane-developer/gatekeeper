#include "bind_policy.h"
#include <string.h>

size_t* rule_count;

aci_rule_t* rule;

aci_rule_condition_t* condition;

aci_rule_operation_t* operation;

void configure_rule(aci_rules_t* rules, const char* label)
{
    rule = &rules->items[rules->count];

    rule_count = &rules->count;

    strcpy(rule->label, label);
}

void configure_exclude_condition(const char* label)
{
    condition = &rule->exclude.items[rule->exclude.count];

    strcpy(condition->label, label);
}

void configure_apply_condition(const char* label)
{
    condition = &rule->apply.items[rule->apply.count];

    strcpy(condition->label, label);
}

void configure_trigger_condition(const char* label)
{
    condition = &rule->trigger.items[rule->trigger.count];

    strcpy(condition->label, label);
}

void configure_operation(aci_rule_operand_type_t operand_type, aci_rule_operation_type_t operation_type, aci_rule_operator_type_t operator_type)
{
    operation = &condition->operations.items[condition->operations.count];

    operation->operation_type = operation_type;

    operation->operator_type = operator_type;

    operation->operand_type = operand_type;
}

void set_integer_operand(uint32_t operand)
{
    operation->operands.items[operation->operands.count++].integer = operand;
}

void set_text_operand(const char* operand)
{
    strcpy(operation->operands.items[operation->operands.count++].text, operand);
}

void register_rule()
{
    *rule_count += 1;
}

void register_exclude_condition()
{
    rule->exclude.count++;
}

void register_apply_condition()
{
    rule->apply.count++;
}

void register_trigger_condition()
{
    rule->trigger.count++;
}

void register_operation()
{
    condition->operations.count++;
}
