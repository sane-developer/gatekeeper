#include <assert.h>
#include <stdio.h>
#include "../../src/utilities/string_utils.h"

#define MAX_BUFFER_SIZE 50

typedef struct
{
    char* label;
    char  entry[MAX_BUFFER_SIZE];
    char  expected_output[MAX_BUFFER_SIZE];
}
test_input_t;

static inline void run_test_case(const test_input_t* input)
{
    printf("Running [%s] test case.\n", input->label);

    char trimmed_entry[MAX_BUFFER_SIZE];

    erase_whitespaces_from_string(input->entry, trimmed_entry);

    assert(matches_string(input->expected_output, trimmed_entry));

    printf("Successfully passed [%s] test case.\n\n", input->label);
}

static inline void entry_is_empty()
{
    const test_input_t input =
    {
        .label = "empty_entry",
        .entry = "",
        .expected_output = ""
    };

    run_test_case(&input);
}

static inline void entry_with_whitespaces()
{
    const test_input_t input =
    {
        .label = "entry_with_whitespaces",
        .entry = "en tr y  with \n  whi te s pac es",
        .expected_output = "entrywithwhitespaces"
    };

    run_test_case(&input);
}

static inline void entry_without_whitespaces()
{
    const test_input_t input =
    {
        .label = "entry_without_whitespaces",
        .entry = "entrywithoutwhitespaces",
        .expected_output = "entrywithoutwhitespaces"
    };

    run_test_case(&input);
}

int main(void)
{
    entry_is_empty();
    entry_with_whitespaces();
    entry_without_whitespaces();
}
