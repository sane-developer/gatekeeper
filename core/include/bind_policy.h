#ifndef BIND_POLICY_H
#define BIND_POLICY_H

#include "aci_rule.h"

///
/// @brief
///
typedef struct
{
    aci_rules_t deny;

    aci_rules_t grant;

    aci_rules_t special;
}
bind_policy_t;

///
/// @brief
/// @param rules
/// @param label
///
void configure_rule(aci_rules_t* rules, const char* label);

///
/// @brief
///
void register_rule();

///
/// @brief
/// @param label
///
void configure_exclude_condition(const char* label);

///
/// @brief
///
void register_exclude_condition();

///
/// @brief
/// @param label
///
void configure_apply_condition(const char* label);

///
/// @brief
///
void register_apply_condition();

///
/// @brief
/// @param label
///
void configure_trigger_condition(const char* label);

///
/// @brief
///
void register_trigger_condition();

///
/// @brief
/// @param operand
/// @param operation
/// @param operator
///
void configure_operation(aci_rule_operand_type_t operand, aci_rule_operation_type_t operation, aci_rule_operator_type_t operator);

///
/// @brief
///
void register_operation();

///
/// @brief
/// @param operand
///
void set_integer_operand(uint32_t operand);

///
/// @brief
/// @param operand
///
void set_text_operand(const char* text);

#endif  // BIND_POLICY_H
