#include "string.h"
#include "../allocators/allocator.h"

static inline char is_white_character(char character)
{
    return isspace(character) != 0;
}

static inline void yoink_contents_from(const char* src, size_t src_length, char* dst, size_t dst_length)
{
    memmove(dst, src, src_length > dst_length ? dst_length : src_length);
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

string_t* string_from_size(size_t size)
{
    const size_t capacity = size + 1;

    const size_t item_size = sizeof(char) * capacity;

    const size_t container_size = sizeof(string_t);

    string_t* string = allocate_memory(container_size);

    string->item = allocate_memory(item_size);

    memset(string->item, 0, item_size);

    string->item[0] = '\0';

    string->size = item_size;

    return string;
}

string_t* string_from_contents(const char* contents)
{
    const size_t capacity = strlen(contents) + 1;

    const size_t item_size = sizeof(char) * capacity;

    const size_t container_size = sizeof(string_t);

    string_t* string = allocate_memory(container_size);

    string->item = allocate_memory(item_size);

    memmove(string->item, contents, item_size);

    string->item[item_size] = '\0';

    string->size = item_size;

    return string;
}

void dispose_string(string_t* string)
{
    if (string->item != NULL)
    {
        free_memory(string->item);
    }

    free_memory(string);
}

char is_empty(const string_t* string)
{
    return strcmp(string->item, "") == 0;
}

char matches_string(const string_t* left, const string_t* right)
{
    return strcmp(left->item, right->item) == 0;
}

char matches_string_literal(const string_t* left, const char* right)
{
    return strcmp(left->item, right) == 0;
}

void remove_contents(const string_t* string)
{
    memset(string->item, 0, string->size);

    string->item[0] = '\0';
}

void yoink_string(const string_t* src, string_t* dst)
{
    yoink_contents_from(src->item, src->size, dst->item, dst->size);
}

void yoink_string_literal(const char* src, string_t* dst)
{
    yoink_contents_from(src, strlen(src), dst->item, dst->size);
}

void erase_whitespaces_from_string(const string_t* src, string_t* dst)
{
    erase_whitespaces_from(src->item, dst->item, dst->size);
}

void erase_whitespaces_from_string_literal(const char* src, string_t* dst)
{
    erase_whitespaces_from(src, dst->item, dst->size);
}