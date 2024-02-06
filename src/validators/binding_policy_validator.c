#include "binding_policy_validator.h"

char validate_binding_policy(const binding_policy_t* policy)
{
    if (!policy)
    {
        return 0;
    }

    return 1;
}