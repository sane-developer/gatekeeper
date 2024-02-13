#include "string.h"
#include "../allocators/allocator.h"

static inline char is_white_character(char character)
{
    return isspace(character) != 0;
}

static inline long find_character_index(const char* src, char character)
{
    long index = 0;

    while (*src++ != '\0')
    {
        if (*src == character)
        {
            return index;
        }

        index++;
    }

    return -1;
}

static inline void yoink(const char* src, size_t src_length, char* dst, size_t dst_length)
{
    const size_t length = src_length > dst_length ? dst_length : src_length;

    memmove(dst, src, length);

    dst[length] = '\0';
}

static inline void erase_whitespaces(const char* src, char* dst, size_t dst_length)
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

    string->item[item_size - 1] = '\0';

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

int is_empty(const string_t* string)
{
    return strcmp(string->item, "") == 0;
}

int matches_string(const string_t* left, const string_t* right)
{
    return strcmp(left->item, right->item) == 0;
}

int matches_string_literal(const string_t* left, const char* right)
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
    yoink(src->item, src->size, dst->item, dst->size);
}

void yoink_string_literal(const char* src, string_t* dst)
{
    yoink(src, strlen(src), dst->item, dst->size);
}

void erase_whitespaces_from_string(const string_t* src, string_t* dst)
{
    erase_whitespaces(src->item, dst->item, dst->size);
}

void erase_whitespaces_from_string_literal(const char* src, string_t* dst)
{
    erase_whitespaces(src, dst->item, dst->size);
}

void split_by_delimiter(const string_t* src, string_t* key, string_t* value, char delimiter)
{
    long delimiter_index = find_character_index(src->item, delimiter);

    yoink(src->item, delimiter_index, key->item, key->size);

    yoink(src->item + delimiter_index + 1, src->size, value->item, value->size);
}

void split_multiple_by_delimiter(const string_t* src, array_t* values, char delimiter)
{
    // Check for NULL pointers or empty string
    if (src == NULL || src->item == NULL || values == NULL) {
        return;
    }

    // Initialize the array
    values->items = NULL;
    values->capacity = 0;
    values->count = 0;

    // Make a copy of the source string
    char* src_copy = strdup(src->item);

    if (src_copy == NULL) {
        return;
    }

    // Initialize strtok_r variables
    char* save_ptr;
    char* token = strtok_r(src_copy, &delimiter, &save_ptr);

    // Tokenize the string and populate the array
    for (; token != NULL; token = strtok_r(NULL, &delimiter, &save_ptr))
    {
        // Allocate memory for the new string
        string_t* new_string = (string_t*)malloc(sizeof(string_t));

        if (new_string == NULL)
        {
            free(src_copy);
            return;
        }

        // Set the item and size in the new string
        new_string->item = strdup(token);
        new_string->size = strlen(token);

        // Check for memory allocation failure
        if (new_string->item == NULL)
        {
            free(new_string);
            free(src_copy);
            return;
        }

        // Add the new string to the array
        if (values->count >= values->capacity)
        {
            values->capacity = (values->capacity == 0) ? 1 : values->capacity * 2;

            values->items = realloc(values->items, values->capacity * sizeof(void*));

            if (values->items == NULL)
            {
                free(new_string->item);
                free(new_string);
                free(src_copy);
                return;
            }
        }

        values->items[values->count++] = new_string;
    }

    // Free the temporary copy of the source string
    free(src_copy);
}