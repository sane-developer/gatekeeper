#include "plugin.h"

bool has_resolved_bind_policy(Slapi_PBlock* block, bind_policy_t* policy)
{
    aci_rule_condition_t managers = (aci_rule_condition_t)
    {
        .label = "managers",
        .is_last = true,
        .operations =
        {
            [0] = (aci_rule_operation_t)
            {
                .operand_type = GROUPS,
                .operation_type = ANY,
                .operator_type = NOP,
                .operands =
                {
                    [0] = (aci_rule_operand_t)
                    {
                        .group = "managers"
                    },
                    [1] = (aci_rule_operand_t)
                    {
                        .group = "executives"
                    }
                }
            }
        }
    };

    aci_rule_condition_t everyone_else = (aci_rule_condition_t)
    {
        .label = "everyone else",
        .is_last = true,
        .operations =
        {
            [0] = (aci_rule_operation_t)
            {
                .operand_type = DN,
                .operation_type = ENDS_WITH,
                .operator_type = NOP,
                .operands =
                {
                    [0] = (aci_rule_operand_t)
                    {
                        .dn = ""
                    }
                }
            }
        }
    };

    aci_rule_condition_t only_in_working_hours = (aci_rule_condition_t)
    {
        .label = "only in working hours",
        .operations =
        {
            [0] = (aci_rule_operation_t)
            {
                .operand_type = TIME,
                .operation_type = BETWEEN,
                .operator_type = OR,
                .operands =
                {
                    [0] = (aci_rule_operand_t)
                    {
                        .time = 1700
                    },
                    [1] = (aci_rule_operand_t)
                    {
                        .time = 2300
                    }
                }
            }
        }
    };

    aci_rule_condition_t only_through_vpn_connection = (aci_rule_condition_t)
    {
        .label = "only through vpn connection",
        .is_last = true,
        .operations =
        {
            [0] = (aci_rule_operation_t)
            {
                .operand_type = IP,
                .operation_type = BETWEEN,
                .operator_type = NOP,
                .operands =
                {
                    [0] = (aci_rule_operand_t)
                    {
                        .ip = 3232235521
                    },
                    [1] = (aci_rule_operand_t)
                    {
                        .ip = 3232235530
                    }
                }
            }
        }
    };

    policy->deny_rules[0] = (aci_rule_t)
    {
        .label = "Deny everyone's access during working hours who are connected via VPN besides managers and executives.",
        .exclude =
        {
            [0] = managers,
        },
        .apply =
        {
            [0] = everyone_else
        },
        .satisfy =
        {
            [0] = only_in_working_hours,
            [1] = only_through_vpn_connection
        }
    };

    return true;
}

int main(void)
{
    bind_request_t request = {0};

    if (!has_resolved_bind_policy(NULL, &plugin_bind_policy))
    {
        printf("%s\n", "Fatal: Could not resolve bind policy.");

        return 1;
    }

    if (has_triggered_any_deny_rule(NULL, &request, &plugin_bind_policy))
    {
        printf("%s\n", "Result: LDAP request denied.");
    }
    else
    {
        printf("%s\n", "Result: LDAP request granted.");
    }

    return 0;
}
