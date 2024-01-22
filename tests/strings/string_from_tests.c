#include <assert.h>
#include <stdio.h>
#include "../../src/types/string.h"

typedef struct
{
    char* label;
    char* entry;
    size_t entry_capacity;
    char expected_equal_capacity;
    char expected_equal_contents;
    char expected_return_value;
}
test_input_t;

static inline void run_test_case(const test_input_t* input)
{
    printf("Running [%s] test case.\n", input->label);

    string_t* string_via_string_literal = string_from_string_literal(input->entry);

    char has_allocated_string_via_string_literal = string_via_string_literal != NULL;
    char have_equal_capacity_via_string_literal;
    char have_equal_contents_via_string_literal;

    if (has_allocated_string_via_string_literal)
    {
        have_equal_capacity_via_string_literal = string_via_string_literal->capacity == input->entry_capacity;
        have_equal_contents_via_string_literal = matches_contents_of_string_literal(string_via_string_literal, input->entry);
    }

    string_t* string_via_string = string_from_string(string_via_string_literal);

    char has_allocated_string_via_string = string_via_string != NULL;
    char have_equal_capacity_via_string;
    char have_equal_contents_via_string;

    if (has_allocated_string_via_string)
    {
        have_equal_capacity_via_string = string_via_string->capacity == input->entry_capacity;
        have_equal_contents_via_string = matches_contents_of_string_literal(string_via_string, input->entry);
    }

    dispose_string(string_via_string_literal);
    dispose_string(string_via_string);

    assert(has_allocated_string_via_string_literal == input->expected_return_value);
    assert(have_equal_capacity_via_string_literal == input->expected_equal_capacity);
    assert(have_equal_contents_via_string_literal == input->expected_equal_contents);

    assert(has_allocated_string_via_string == input->expected_return_value);
    assert(have_equal_capacity_via_string == input->expected_equal_capacity);
    assert(have_equal_contents_via_string == input->expected_equal_contents);

    printf("Successfully passed [%s] test case.\n\n", input->label);
}

static inline void entry_is_null()
{
    const test_input_t input =
    {
        .label = "entry is null",
        .entry = NULL,
        .entry_capacity = 0,
        .expected_equal_capacity = 0,
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
        .entry_capacity = 1,
        .expected_equal_capacity = 1,
        .expected_equal_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

static inline void entry_has_contents()
{
    const test_input_t input =
    {
        .label = "entry has contents",
        .entry = "entry",
        .entry_capacity = strlen("entry") + 1,
        .expected_equal_capacity = 1,
        .expected_equal_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

int main(void)
{
    entry_is_null();
    entry_is_empty();
    entry_has_contents();
}