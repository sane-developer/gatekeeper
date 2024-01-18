#include <assert.h>
#include <stdio.h>
#include "../../src/utilities/string_utils.h"

#define MAX_ENTRY_SIZE 30
#define MAX_KEY_SIZE 3
#define MAX_VALUE_SIZE 5

typedef struct
{
    char* label;
    char  delimiter;
    char* entry;
    char* expected_key;
    char* expected_value;
}
test_input_t;

static inline void run_test_case(const test_input_t* input)
{
    printf("Running [%s] test case.\n", input->label);

    string_t entry;

    initialize_string(&entry, MAX_ENTRY_SIZE, input->entry);

    string_t key;

    initialize_empty_string(&key, MAX_KEY_SIZE);

    string_t value;

    initialize_empty_string(&value, MAX_VALUE_SIZE);

    extract_key_value_pair_from_string(&entry, &key, &value, input->delimiter);

    char is_matching_key = matches_string(input->expected_key, key.item);

    char is_matching_value = matches_string(input->expected_value, value.item);

    dispose_string(&entry);

    dispose_string(&key);

    dispose_string(&value);

    assert(is_matching_key);

    assert(is_matching_value);

    printf("Successfully passed [%s] test case.\n\n", input->label);
}

static inline void entry_is_empty()
{
    const test_input_t input =
    {
        .label = "entry_is_empty",
        .delimiter = '=',
        .entry = "",
        .expected_key = "",
        .expected_value = ""
    };

    run_test_case(&input);
}

static inline void entry_without_delimiter()
{
    const test_input_t input =
    {
        .label = "entry_without_delimiter",
        .delimiter = '=',
        .entry = "key",
        .expected_key = "key",
        .expected_value = ""
    };

    run_test_case(&input);
}

static inline void entry_with_delimiter_only()
{
    const test_input_t input =
    {
        .label = "entry_with_delimiter_only",
        .delimiter = '=',
        .entry = "=",
        .expected_key = "",
        .expected_value = ""
    };

    run_test_case(&input);
}

static inline void entry_with_key_and_delimiter()
{
    const test_input_t input =
    {
        .label = "entry_with_key_and_delimiter",
        .delimiter = '=',
        .entry = "key=",
        .expected_key = "key",
        .expected_value = ""
    };

    run_test_case(&input);
}

static inline void entry_with_delimiter_and_value()
{
    const test_input_t input =
    {
        .label = "entry_with_delimiter_and_value",
        .delimiter = '=',
        .entry = "=value",
        .expected_key = "",
        .expected_value = "value"
    };

    run_test_case(&input);
}

static inline void entry_with_key_and_delimiter_and_value()
{
    const test_input_t input =
    {
        .label = "entry_with_key_and_delimiter_and_value",
        .delimiter = '=',
        .entry = "key=value",
        .expected_key = "key",
        .expected_value = "value"
    };

    run_test_case(&input);
}

static inline void entry_with_key_exceeding_allocated_length()
{
    const test_input_t input =
    {
        .label = "entry_with_key_exceeding_allocated_length",
        .delimiter = '=',
        .entry = "keykey=value",
        .expected_key = "key",
        .expected_value = "value"
    };

    run_test_case(&input);
}

static inline void entry_with_value_exceeding_allocated_length()
{
    const test_input_t input =
    {
        .label = "entry_with_value_exceeding_allocated_length",
        .delimiter = '=',
        .entry = "key=valuevalue",
        .expected_key = "key",
        .expected_value = "value"
    };

    run_test_case(&input);
}

int main(void)
{
    entry_is_empty();
    entry_without_delimiter();
    entry_with_delimiter_only();
    entry_with_key_and_delimiter();
    entry_with_delimiter_and_value();
    entry_with_key_and_delimiter_and_value();
    entry_with_key_exceeding_allocated_length();
    entry_with_value_exceeding_allocated_length();
}
