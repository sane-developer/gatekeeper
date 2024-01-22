#include <assert.h>
#include <stdio.h>
#include "../../src/types/string.h"

typedef struct
{
    char* label;
    char* entry;
    size_t dst_capacity;
    char* expected_string_value;
    char expected_equal_contents;
    char expected_return_value;
}
test_input_t;

static inline void run_test_case(const test_input_t* input)
{
    printf("Running [%s] test case.\n", input->label);

    string_t* scattered_string = string_from_string_literal(input->entry);
    string_t* condensed_string = string_from_size(input->dst_capacity);

    char has_erased_via_string_literal = erase_whitespaces_from_string_literal(input->entry, condensed_string);
    char are_matching_via_string_literal;

    if (has_erased_via_string_literal)
    {
        are_matching_via_string_literal = matches_contents_of_string_literal(condensed_string, input->expected_string_value);
    }

    clear_contents_of(condensed_string);

    char has_erased_via_string = erase_whitespaces_from_string(scattered_string, condensed_string);
    char are_matching_via_string;

    if (has_erased_via_string)
    {
        are_matching_via_string = matches_contents_of_string_literal(condensed_string, input->expected_string_value);
    }

    dispose_string(scattered_string);
    dispose_string(condensed_string);

    assert(has_erased_via_string == input->expected_return_value);
    assert(are_matching_via_string == input->expected_equal_contents);

    assert(has_erased_via_string_literal == input->expected_return_value);
    assert(are_matching_via_string_literal == input->expected_equal_contents);

    printf("Successfully passed [%s] test case.\n\n", input->label);
}

static inline void entry_is_null()
{
    const test_input_t input =
    {
        .label = "entry is null",
        .entry = NULL,
        .dst_capacity = 0,
        .expected_string_value = NULL,
        .expected_equal_contents = 0,
        .expected_return_value = 0
    };

    run_test_case(&input);
}

static inline void entry_is_empty()
{
    const test_input_t input =
    {
        .label = "entry is empty",
        .entry = "",
        .dst_capacity = 1,
        .expected_string_value = "",
        .expected_equal_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

static inline void entry_with_whitespaces()
{
    const test_input_t input =
    {
        .label = "entry with whitespaces",
        .entry = "    to  \n\n be \t condensed \r ",
        .dst_capacity = strlen("    to  \n\n be \t condensed \r ") + 1,
        .expected_string_value = "tobecondensed",
        .expected_equal_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

static inline void entry_without_whitespaces()
{
    const test_input_t input =
    {
        .label = "entry without whitespaces",
        .entry = "already_erased",
        .dst_capacity = strlen("already_erased") + 1,
        .expected_string_value = "already_erased",
        .expected_equal_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

int main(void)
{
    entry_is_null();
    entry_is_empty();
    entry_with_whitespaces();
    entry_without_whitespaces();
}