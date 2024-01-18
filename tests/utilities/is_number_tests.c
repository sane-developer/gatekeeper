#include <assert.h>
#include <stdio.h>
#include "../../src/utilities/string_utils.h"

typedef struct
{
    char* label;
    char* entry;
    char  expected_output;
}
test_input_t;

static inline void run_test_case(const test_input_t* input)
{
    printf("Running [%s] test case.\n", input->label);

    assert(is_number(input->entry) == input->expected_output);

    printf("Successfully passed [%s] test case.\n\n", input->label);
}

static inline void entry_is_empty()
{
    const test_input_t input =
    {
        .label = "entry_is_empty",
        .entry = "",
        .expected_output = 0,
    };

    run_test_case(&input);
}

static inline void entry_with_whitespaces()
{
    const test_input_t input =
    {
        .label = "entry_with_whitespaces",
        .entry = "",
        .expected_output = 0,
    };

    run_test_case(&input);
}

static inline void entry_with_numerical_characters_only()
{
    const test_input_t input =
    {
        .label = "entry_with_numerical_characters_only",
        .entry = "636",
        .expected_output = 1,
    };

    run_test_case(&input);
}

static inline void entry_with_non_numerical_characters_only()
{
    const test_input_t input =
    {
        .label = "entry_with_non_numerical_characters_only",
        .entry = "test",
        .expected_output = 0,
    };

    run_test_case(&input);
}

static inline void entry_with_numerical_and_other_characters()
{
    const test_input_t input =
    {
        .label = "entry_with_numerical_and_other_characters",
        .entry = "test10000test",
        .expected_output = 0,
    };

    run_test_case(&input);
}

int main(void)
{
    entry_is_empty();
    entry_with_whitespaces();
    entry_with_numerical_characters_only();
    entry_with_non_numerical_characters_only();
    entry_with_numerical_and_other_characters();
}