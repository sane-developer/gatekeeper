#include "bind_policy.h"
#include <string.h>

size_t* rules_count;

aci_rule_t* rule;

aci_rule_condition_t* rule_condition;

aci_rule_operation_t* rule_operation;

void configure_rule(aci_rules_t* rules, const char* label)
{
    rule = &rules->items[rules->count];

    rules_count = &rules->count;

    strcpy(rule->label, label);
}

void configure_exclude_condition(const char* label)
{
    rule_condition = &rule->exclude.items[rule->exclude.count];

    strcpy(rule_condition->label, label);
}

void configure_apply_condition(const char* label)
{
    rule_condition = &rule->apply.items[rule->apply.count];

    strcpy(rule_condition->label, label);
}

void configure_trigger_condition(const char* label)
{
    rule_condition = &rule->trigger.items[rule->trigger.count];

    strcpy(rule_condition->label, label);
}

void configure_operation(aci_rule_operand_type_t operand, aci_rule_operation_type_t operation, aci_rule_operator_type_t operator)
{
    rule_operation = &rule_condition->operations.items[rule_condition->operations.count];

    rule_operation->operation_type = operation;

    rule_operation->operator_type = operator;

    rule_operation->operand_type = operand;
}

void set_integer_operand(uint32_t operand)
{
    rule_operation->operands.items[rule_operation->operands.count++].integer = operand;
}

void set_text_operand(const char* operand)
{
    strcpy(rule_operation->operands.items[rule_operation->operands.count++].text, operand);
}

void register_rule()
{
    *rules_count += 1;
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
    rule_condition->operations.count++;
}
