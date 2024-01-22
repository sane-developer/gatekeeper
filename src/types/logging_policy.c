#include <stddef.h>
#include "logging_policy.h"
#include "../allocators/allocator.h"

logging_policy_t* allocate_logging_policy()
{
    const size_t policy_size = sizeof(logging_policy_t);

    return (logging_policy_t*) allocate_memory(policy_size);
}

void dispose_logging_policy(logging_policy_t* policy)
{
    if (policy != NULL)
    {
        free_memory(policy);
    }
}