#include "string.h"

static inline char is_white_character(char character)
{
    return isspace(character) != 0;
}

static inline size_t get_string_length(const string_t* string)
{
    return string->capacity - 1;
}

static inline size_t get_string_literal_length(const char* buffer)
{
    return strlen(buffer);
}

static inline string_t* string_from(const char* contents, size_t capacity)
{
    string_t* string = (string_t*) allocate_memory(sizeof(string_t));

    if (string == NULL)
    {
        return NULL;
    }

    string->item = (char*) allocate_memory(sizeof(char) * capacity);

    if (string->item == NULL)
    {
        free_memory(string);

        return NULL;
    }

    const size_t length = capacity - 1;

    if (contents != NULL)
    {
        memmove(string->item, contents, length);

        string->item[length] = '\0';
    }
    else
    {
        memset(string->item, 0, capacity);

        string->item[0] = '\0';
    }

    string->capacity = capacity;

    return string;
}

static inline void yoink_contents_from(const char* src, size_t src_length, char* dst, size_t dst_length)
{
    const size_t bytes_to_copy = src_length > dst_length ? dst_length : src_length;

    memmove(dst, src, bytes_to_copy);
}

static inline void erase_whitespaces_from(const char* src, char* dst, size_t dst_length)
{
    size_t moved_characters_count = 0;

    while (*src != '\0' && moved_characters_count <= dst_length)
    {
        if (!is_white_character(*src))
        {
            *dst++ = *src;

            moved_characters_count++;
        }

        src++;
    }

    dst[moved_characters_count] = '\0';
}

string_t* string_from_size(size_t capacity)
{
    if (capacity == 0)
    {
        return NULL;
    }

    return string_from(NULL, capacity);
}

string_t* string_from_string(const string_t* string)
{
    if (string == NULL || string->item == NULL)
    {
        return NULL;
    }

    return string_from(string->item, string->capacity);
}

string_t* string_from_string_literal(const char* buffer)
{
    if (buffer == NULL)
    {
        return NULL;
    }

    const size_t capacity = get_string_literal_length(buffer) + 1;

    return string_from(buffer, capacity);
}

void dispose_string(string_t* string)
{
    if (string == NULL)
    {
        return;
    }

    if (string->item != NULL)
    {
        free_memory(string->item);
    }

    free_memory(string);
}

char clear_contents_of(const string_t* string)
{
    if (string == NULL || string->item == NULL)
    {
        return 0;
    }

    const size_t length = get_string_length(string);

    memset(string->item, 0, length);

    string->item[0] = '\0';

    return 1;
}

char is_empty(const string_t* string)
{
    if (string == NULL || string->item == NULL)
    {
        return 0;
    }

    return strcmp(string->item, "") == 0;
}

char matches_contents_of_string(const string_t* left, const string_t* right)
{
    if (left == NULL || left->item == NULL)
    {
        return 0;
    }

    if (right == NULL || right->item == NULL)
    {
        return 0;
    }

    return strcmp(left->item, right->item) == 0;
}

char matches_contents_of_string_literal(const string_t* left, const char* right)
{
    if (left == NULL || left->item == NULL)
    {
        return 0;
    }

    if (right == NULL)
    {
        return 0;
    }

    return strcmp(left->item, right) == 0;
}

char yoink_contents_from_string(const string_t* src, string_t* dst)
{
    if (src == NULL || src->item == NULL)
    {
        return 0;
    }

    if (dst == NULL || dst->item == NULL)
    {
        return 0;
    }

    const size_t src_length = get_string_length(src);
    const size_t dst_length = get_string_length(dst);

    yoink_contents_from(src->item, src_length, dst->item, dst_length);

    return 1;
}

char yoink_contents_from_string_literal(const char* src, string_t* dst)
{
    if (src == NULL)
    {
        return 0;
    }

    if (dst == NULL || dst->item == NULL)
    {
        return 0;
    }

    const size_t src_length = get_string_literal_length(src);
    const size_t dst_length = get_string_length(dst);

    yoink_contents_from(src, src_length, dst->item, dst_length);

    return 1;
}

char erase_whitespaces_from_string(const string_t* src, string_t* dst)
{
    if (src == NULL || src->item == NULL)
    {
        return 0;
    }

    if (dst == NULL || dst->item == NULL)
    {
        return 0;
    }

    const size_t dst_length = get_string_length(dst);

    erase_whitespaces_from(src->item, dst->item, dst_length);

    return 1;
}

char erase_whitespaces_from_string_literal(const char* src, string_t* dst)
{
    if (src == NULL)
    {
        return 0;
    }

    if (dst == NULL || dst->item == NULL)
    {
        return 0;
    }

    const size_t dst_length = get_string_length(dst);

    erase_whitespaces_from(src, dst->item, dst_length);

    return 1;
}