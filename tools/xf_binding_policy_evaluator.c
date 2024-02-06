#include <assert.h>
#include <stdio.h>
#include "../src/loggers/logger.h"
#include "../src/parsers/binding_policy_parser.h"
#include "../src/validators/binding_policy_validator.h"

static inline FILE* get_policy_file(int argc, char** argv)
{
    assert(argc > 0 && "Path to policy file has not been provided.");

    const char* path = argv[1];

    assert(path && "Path to policy file was NULL.");

    FILE* file = fopen("./test.conf", "r");

    assert(file && "Could not open the file at specified path.");

    return file;
}

int main(int argc, char** argv)
{
    FILE* policy_file = get_policy_file(argc, argv);

    binding_policy_t* policy = parse_binding_policy(policy_file);

    char is_valid = validate_binding_policy(policy);

    if (is_valid)
    {
        log_info("File contains valid binding policy based on xf standard.");
    }
    else
    {
        log_critical("File contains invalid binding policy based on xf standard.");
    }

    dispose_binding_policy(policy);
}