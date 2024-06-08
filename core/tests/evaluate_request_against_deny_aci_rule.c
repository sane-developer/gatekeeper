#include "plugin.h"

bool has_resolved_plugin_bind_policy(Slapi_PBlock* block, aci_rules_t* grant_rules, aci_rules_t* deny_rules)
{
    return false; // TODO: Implement based on business requirements.
}

int main(void)
{
    bind_request_t request = {0};

    if (!has_resolved_plugin_bind_policy(NULL, &plugin_grant_aci_rules, &plugin_deny_aci_rules))
    {
        printf("%s\n", "Fatal: Could not resolve bind policy.");

        return 1;
    }

    if (has_triggered_any_deny_rule(NULL, &request, &plugin_deny_aci_rules))
    {
        printf("%s\n", "Result: LDAP request denied.");
    }
    else
    {
        printf("%s\n", "Result: LDAP request granted.");
    }

    return 0;
}
