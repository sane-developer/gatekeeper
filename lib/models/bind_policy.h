#ifndef BIND_POLICY_H
#define BIND_POLICY_H

///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    struct aci_rule_t* grant_rules;

    ///
    /// @brief
    ///
    struct aci_rule_t* deny_rules;
}
bind_policy_t;

#endif  // BIND_POLICY_H
