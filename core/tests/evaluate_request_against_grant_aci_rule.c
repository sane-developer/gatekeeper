#include "plugin.h"

bool has_resolved_bind_policy(Slapi_PBlock* block, bind_policy_t* policy)
{
    return false;
}

int main(void)
{
    bind_request_t request = {0};

    if (!has_resolved_bind_policy(NULL, &plugin_bind_policy))
    {
        printf("%s\n", "Fatal: Could not resolve bind policy.");

        return 1;
    }

    if (has_triggered_any_grant_rule(NULL, &request, &plugin_bind_policy))
    {
        printf("%s\n", "Result: LDAP request denied.");
    }
    else
    {
        printf("%s\n", "Result: LDAP request granted.");
    }

    return 0;
}
