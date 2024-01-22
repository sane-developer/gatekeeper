#include <assert.h>
#include <stdio.h>
#include "../../src/allocators/allocator.h"
#include "../../src/parsers/logging_policy_parser.h"

typedef struct
{
    char* label;
    char* file_path;
    logging_strategy_t expected_accepted_requests_strategy;
    logging_strategy_t expected_denied_requests_strategy;
    logging_policy_parser_events_t expected_occurred_events;
}
test_input_t;

static inline void run_test_case(const test_input_t* input)
{
    printf("Running [%s] test case.\n", input->label);

    FILE* test_file = fopen(input->file_path, "r");

    assert(test_file != NULL);

    logging_policy_t policy =
    {
        .accepted_requests_strategy = 0,
        .denied_requests_strategy = 0
    };

    logging_policy_parser_events_t events = parse_logging_policy_file(&policy, test_file);

    assert(input->expected_occurred_events == events);
    assert(input->expected_accepted_requests_strategy == policy.accepted_requests_strategy);
    assert(input->expected_denied_requests_strategy == policy.denied_requests_strategy);

    printf("Successfully passed [%s] test case.\n\n", input->label);
}

static inline void configuration_file_contains_out_of_bounds_entries_test(void)
{
    const test_input_t input =
    {
        .label = "configuration file contains out of bounds entries",
        .file_path = "resources/logging-policy-parser/out-of-bounds-entries/logging.conf",
        .expected_occurred_events = found_accepted_requests_strategy_label | found_denied_requests_strategy_label,
        .expected_accepted_requests_strategy = include_user_dn,
        .expected_denied_requests_strategy = include_user_dn
    };

    run_test_case(&input);
}

static inline void accepted_requests_strategy_without_any_options_test(void)
{
    const test_input_t input =
    {
        .label = "accepted requests strategy without any options",
        .file_path = "resources/logging-policy-parser/strategies-without-entries/accepted-requests-strategy.conf",
        .expected_occurred_events = found_accepted_requests_strategy_label | found_denied_requests_strategy_label,
        .expected_accepted_requests_strategy = 0,
        .expected_denied_requests_strategy = include_user_dn
    };

    run_test_case(&input);
}

static inline void denied_requests_strategy_without_any_options_test(void)
{
    const test_input_t input =
    {
        .label = "denied requests strategy without any options",
        .file_path = "resources/logging-policy-parser/strategies-without-entries/denied-requests-strategy.conf",
        .expected_occurred_events = found_accepted_requests_strategy_label | found_denied_requests_strategy_label,
        .expected_accepted_requests_strategy = include_user_dn,
        .expected_denied_requests_strategy = 0
    };

    run_test_case(&input);
}

static inline void both_requests_strategies_without_any_options_test(void)
{
    const test_input_t input =
    {
        .label = "both requests strategies without any options",
        .file_path = "resources/logging-policy-parser/strategies-without-entries/both-requests-strategies.conf",
        .expected_occurred_events = found_accepted_requests_strategy_label | found_denied_requests_strategy_label,
        .expected_accepted_requests_strategy = 0,
        .expected_denied_requests_strategy = 0
    };

    run_test_case(&input);
}

static inline void accepted_requests_strategy_missing_from_configuration_test(void)
{
    const test_input_t input =
    {
        .label = "accepted requests strategy missing from configuration",
        .file_path = "resources/logging-policy-parser/missing-strategy-labels/accepted-requests-strategy.conf",
        .expected_occurred_events = found_denied_requests_strategy_label,
        .expected_accepted_requests_strategy = 0,
        .expected_denied_requests_strategy = include_user_dn
    };

    run_test_case(&input);
}

static inline void denied_requests_strategy_missing_from_configuration_test(void)
{
    const test_input_t input =
    {
        .label = "denied requests strategy missing from configuration",
        .file_path = "resources/logging-policy-parser/missing-strategy-labels/denied-requests-strategy.conf",
        .expected_occurred_events = found_accepted_requests_strategy_label,
        .expected_accepted_requests_strategy = include_user_dn,
        .expected_denied_requests_strategy = 0
    };

    run_test_case(&input);
}

static inline void both_requests_strategies_missing_from_configuration_test(void)
{
    const test_input_t input =
    {
        .label = "both requests strategies missing from configuration",
        .file_path = "resources/logging-policy-parser/missing-strategy-labels/both-requests-strategies.conf",
        .expected_occurred_events = 0,
        .expected_accepted_requests_strategy = 0,
        .expected_denied_requests_strategy = 0
    };

    run_test_case(&input);
}

static inline void accepted_requests_strategy_contains_unresolvable_entries_test(void)
{
    const test_input_t input =
    {
        .label = "accepted requests strategy contains unresolvable entries",
        .file_path = "resources/logging-policy-parser/unresolvable-entries/accepted-requests-strategy.conf",
        .expected_occurred_events = found_accepted_requests_strategy_label | found_denied_requests_strategy_label,
        .expected_accepted_requests_strategy = 0,
        .expected_denied_requests_strategy = include_user_dn
    };

    run_test_case(&input);
}

static inline void denied_requests_strategy_contains_unresolvable_entries_test(void)
{
    const test_input_t input =
    {
        .label = "denied requests strategy contains unresolvable entries",
        .file_path = "resources/logging-policy-parser/unresolvable-entries/denied-requests-strategy.conf",
        .expected_occurred_events = found_accepted_requests_strategy_label | found_denied_requests_strategy_label,
        .expected_accepted_requests_strategy = include_user_dn,
        .expected_denied_requests_strategy = 0
    };

    run_test_case(&input);
}

static inline void both_requests_strategies_contains_unresolvable_entries_test(void)
{
    const test_input_t input =
    {
        .label = "both requests strategies contains unresolvable entries",
        .file_path = "resources/logging-policy-parser/unresolvable-entries/both-requests-strategies.conf",
        .expected_occurred_events = found_accepted_requests_strategy_label | found_denied_requests_strategy_label,
        .expected_accepted_requests_strategy = 0,
        .expected_denied_requests_strategy = 0
    };

    run_test_case(&input);
}

static inline void accepted_requests_strategy_contains_duplicate_entries_test(void)
{
    const test_input_t input =
    {
        .label = "accepted requests strategy contains duplicates",
        .file_path = "resources/logging-policy-parser/duplicate-entries/accepted-requests-strategy.conf",

        .expected_occurred_events =
            found_accepted_requests_strategy_label |
            found_denied_requests_strategy_label,

        .expected_accepted_requests_strategy =
            include_user_dn |
            include_rule_name |
            include_evaluation,

        .expected_denied_requests_strategy =
            include_date |
            include_sasl_method
    };

    run_test_case(&input);
}

static inline void denied_requests_strategy_contains_duplicate_entries_test(void)
{
    const test_input_t input =
    {
        .label = "denied requests strategy contains duplicates",
        .file_path = "resources/logging-policy-parser/duplicate-entries/denied-requests-strategy.conf",

        .expected_occurred_events =
            found_accepted_requests_strategy_label |
            found_denied_requests_strategy_label,

        .expected_accepted_requests_strategy =
            include_user_ip |
            include_user_dn,

        .expected_denied_requests_strategy =
            include_user_dn |
            include_evaluation |
            include_authentication_method
    };

    run_test_case(&input);
}

static inline void both_requests_strategies_contain_duplicate_entries_test(void)
{
    const test_input_t input =
    {
        .label = "both requests strategies contain duplicates",
        .file_path = "resources/logging-policy-parser/duplicate-entries/both-requests-strategies.conf",

        .expected_occurred_events =
            found_accepted_requests_strategy_label |
            found_denied_requests_strategy_label,

        .expected_accepted_requests_strategy =
            include_user_dn |
            include_user_ip |
            include_evaluation |
            include_date,

        .expected_denied_requests_strategy =
            include_evaluation |
            include_date |
            include_sasl_method
    };

    run_test_case(&input);
}

static inline void accepted_requests_strategy_declared_multiple_times_test(void)
{
    const test_input_t input =
    {
        .label = "accepted requests strategy split into separate entries",
        .file_path = "resources/logging-policy-parser/multiple-strategy-declarations/accepted-requests-strategy.conf",

        .expected_occurred_events =
            found_accepted_requests_strategy_label |
            found_denied_requests_strategy_label,

        .expected_accepted_requests_strategy =
            include_user_dn |
            include_user_ip |
            include_evaluation |
            include_date,

        .expected_denied_requests_strategy =
            include_rule_name |
            include_authentication_method
    };

    run_test_case(&input);
}

static inline void denied_requests_strategy_declared_multiple_times_test(void)
{
    const test_input_t input =
    {
        .label = "denied requests strategy split into separate entries",
        .file_path = "resources/logging-policy-parser/multiple-strategy-declarations/denied-requests-strategy.conf",

        .expected_occurred_events =
            found_accepted_requests_strategy_label |
            found_denied_requests_strategy_label,

        .expected_accepted_requests_strategy =
            include_user_ip |
            include_evaluation,

        .expected_denied_requests_strategy =
            include_user_dn |
            include_authentication_method |
            include_date
    };

    run_test_case(&input);
}

static inline void both_requests_strategies_declared_multiple_times_test(void)
{
    const test_input_t input =
    {
        .label = "both requests strategies split into separate entries",
        .file_path = "resources/logging-policy-parser/multiple-strategy-declarations/both-requests-strategies.conf",

        .expected_occurred_events =
            found_accepted_requests_strategy_label |
            found_denied_requests_strategy_label,

        .expected_accepted_requests_strategy =
            include_user_dn |
            include_user_ip |
            include_evaluation |
            include_sasl_method,

        .expected_denied_requests_strategy =
            include_user_dn |
            include_date |
            include_authentication_method |
            include_sasl_method
    };

    run_test_case(&input);
}

int main(void)
{
    configuration_file_contains_out_of_bounds_entries_test();

    accepted_requests_strategy_without_any_options_test();
    denied_requests_strategy_without_any_options_test();
    both_requests_strategies_without_any_options_test();

    accepted_requests_strategy_missing_from_configuration_test();
    denied_requests_strategy_missing_from_configuration_test();
    both_requests_strategies_missing_from_configuration_test();

    accepted_requests_strategy_contains_duplicate_entries_test();
    denied_requests_strategy_contains_duplicate_entries_test();
    both_requests_strategies_contain_duplicate_entries_test();

    accepted_requests_strategy_declared_multiple_times_test();
    denied_requests_strategy_declared_multiple_times_test();
    both_requests_strategies_declared_multiple_times_test();

    accepted_requests_strategy_contains_unresolvable_entries_test();
    denied_requests_strategy_contains_unresolvable_entries_test();
    both_requests_strategies_contains_unresolvable_entries_test();
}