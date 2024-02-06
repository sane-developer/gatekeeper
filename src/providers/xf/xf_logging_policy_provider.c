#include <stdio.h>
#include "../logging_policy_provider.h"
#include "../../parsers/xf/xf_logging_policy_parser.h"
#include "../../validators/logging_policy_validator.h"

logging_policy_t* supply_logging_policy(void* resource)
{
    const char* path = (char*) resource;

    FILE* file = fopen(path, "r");

    if (file == NULL)
    {
        return NULL;
    }

    logging_policy_t* policy = create_logging_policy();

    parser_events_t events = parse_logging_policy(policy, file);

    char is_valid = validate_logging_policy(policy);

    if (!is_valid)
    {
        dispose_logging_policy(policy);
        return NULL;
    }

    return policy;
}