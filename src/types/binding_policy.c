#include "binding_policy.h"
#include "../allocators/allocator.h"

binding_policy_t* create_binding_policy()
{
    const size_t policy_size = sizeof(binding_policy_t);

    return (binding_policy_t*) allocate_memory(policy_size);
}

void dispose_binding_policy(binding_policy_t* policy)
{
    if (policy != NULL)
    {
        free_memory(policy);
    }
}