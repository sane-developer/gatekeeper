#ifndef ACI_RULE_CONDITION_PARAMETER_H_
#define ACI_RULE_CONDITION_PARAMETER_H_

///
/// @brief Represents the bind request parameters that may be evaluated via custom ACI rules.
///
typedef enum
{
    ///
    /// @brief Numerical value indicating that DN should be evaluated.
    ///
    DN,
    
    ///
    /// @brief Numerical value indicating that IP address should be evaluated. 
    ///
    IP,

    ///
    /// @brief Numerical value indicating that DNS address should be evaluated. 
    ///
    DNS,

    ///
    /// @brief Numerical value indicating that authentication method should be evaluated.
    ///
    AUTH,

    ///
    /// @brief Numerical value indicating that roles of the LDAP client should be evaluated.
    ///
    ROLES,

    ///
    /// @brief Numerical value indicating that groups of the LDAP client should be evaluated.
    ///
    GROUPS,

    ///
    /// @brief Numerical value indicating that attributes of the LDAP client should be evaluated.
    ///
    ATTRIBUTES,

    ///
    /// @brief Numerical value indicating that day of week should be evaluated.
    ///
    DAY_OF_WEEK,

    ///
    /// @brief Numerical value indicating that time of day should be evaluated.
    ///
    TIME_OF_DAY
}
aci_rule_condition_parameter_t;

#endif  // ACI_RULE_CONDITION_PARAMETER_H_
