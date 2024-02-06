#include "logging_policy.h"
#include "../allocators/allocator.h"

logging_policy_t* create_logging_policy()
{
    const size_t policy_size = sizeof(logging_policy_t);

    logging_policy_t* policy = allocate_memory(policy_size);

    *policy = (logging_policy_t)
    {
        .accepted_requests_strategy = uninitialized_strategy,
        .denied_requests_strategy = uninitialized_strategy
    };

    return policy;
}

void dispose_logging_policy(logging_policy_t* policy)
{
    free_memory(policy);
}