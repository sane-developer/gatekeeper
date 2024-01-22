#include <assert.h>
#include <stdio.h>
#include "../../src/types/string.h"

typedef struct
{
    char* label;
    char* entry;
    size_t dst_capacity;
    char* expected_string_value;
    char expected_yoink_of_contents;
    char expected_return_value;
}
test_input_t;

static inline void run_test_case(const test_input_t* input)
{
    printf("Running [%s] test case.", input->label);

    string_t* src = string_from_string_literal(input->entry);
    string_t* dst = string_from_size(input->dst_capacity);

    char has_yoinked_contents_from_string_literal = yoink_contents_from_string_literal(input->entry, dst);
    char has_yoinked_expected_contents_from_string_literal;

    if (has_yoinked_contents_from_string_literal)
    {
        has_yoinked_expected_contents_from_string_literal = matches_contents_of_string_literal(dst, input->expected_string_value);
    }

    clear_contents_of(dst);

    char has_yoinked_contents_from_string = yoink_contents_from_string(src, dst);
    char has_yoinked_expected_contents_from_string;

    if (has_yoinked_contents_from_string)
    {
        has_yoinked_expected_contents_from_string = matches_contents_of_string_literal(dst, input->expected_string_value);
    }

    dispose_string(src);
    dispose_string(dst);

    assert(has_yoinked_contents_from_string_literal == input->expected_return_value);
    assert(has_yoinked_expected_contents_from_string_literal == input->expected_yoink_of_contents);

    assert(has_yoinked_contents_from_string == input->expected_return_value);
    assert(has_yoinked_expected_contents_from_string == input->expected_yoink_of_contents);

    printf("Successfully passed [%s] test case.\n", input->label);
}

static inline void entry_is_null()
{
    const test_input_t input =
    {
        .label = "entry is null",
        .entry = NULL,
        .dst_capacity = 0,
        .expected_string_value = NULL,
        .expected_yoink_of_contents = 0,
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
        .expected_yoink_of_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

static inline void entry_capacity_equals_dst_capacity()
{
    const test_input_t input =
    {
        .label = "entry capacity equals dst capacity",
        .entry = "test",
        .dst_capacity = strlen("test") + 1,
        .expected_string_value = "test",
        .expected_yoink_of_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

static inline void entry_capacity_is_larger_than_dst_capacity()
{
    const test_input_t input =
    {
        .label = "entry capacity is larger than dst capacity",
        .entry = "test",
        .dst_capacity = 3,
        .expected_string_value = "te",
        .expected_yoink_of_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

static inline void entry_capacity_is_smaller_than_dst_capacity()
{
    const test_input_t input =
    {
        .label = "entry capacity is smaller than dst capacity",
        .entry = "test",
        .dst_capacity = 10,
        .expected_string_value = "test",
        .expected_yoink_of_contents = 1,
        .expected_return_value = 1
    };

    run_test_case(&input);
}

int main(void)
{
    entry_is_null();
    entry_is_empty();
    entry_capacity_equals_dst_capacity();
    entry_capacity_is_larger_than_dst_capacity();
    entry_capacity_is_smaller_than_dst_capacity();
}