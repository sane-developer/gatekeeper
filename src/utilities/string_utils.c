#include "string_utils.h"

static inline size_t find_first_occurrence(const char* src, char target)
{
    size_t index = 0;

    while (*src != '\0')
    {
        if (*src == target)
        {
            return index;
        }

        index++;
        src++;
    }

    return -1;
}

void initialize_string(string_t* src, size_t size, const char* content)
{
    if (!src)
    {
        return;
    }

    src->size = size;

    src->item = (char*) malloc(size * sizeof(char));

    clear_buffer(src->item, size);

    if (content)
    {
        move_bytes(content, src->item, strlen(content));
    }
}

void dispose_string(string_t* src)
{
    free(src->item);

    src->size = 0;
}

char is_number(const char* src)
{
    if (!src)
    {
        return 0;
    }

    if (matches_empty_string(src))
    {
        return 0;
    }

    while (*src != '\0')
    {
        if (!isdigit(*src))
        {
            return 0;
        }

        src++;
    }

    return 1;
}

char convert_string_to_integer(const char* src, int* dst)
{
    if (!dst)
    {
        return 0;
    }

    if (!is_number(src))
    {
        return 0;
    }

    char* last_character;

    int value = (int) strtol(src, &last_character, 10);

    *dst = value;

    return 1;
}

void erase_whitespaces_from_string(const char* scattered, char* condensed)
{
    if (!scattered || !condensed)
    {
        return;
    }

    while (*scattered != '\0')
    {
        if (!isspace(*scattered))
        {
            *condensed++ = *scattered;
        }

        scattered++;
    }

    *condensed = '\0';
}

void extract_key_value_pair_from_string(const string_t* entry, string_t* key, string_t* value, char delimiter)
{
    if (!entry || !entry->item)
    {
        return;
    }

    if (!key || !key->item)
    {
        return;
    }

    if (!value || !value->item)
    {
        return;
    }

    clear_buffer(key->item, key->size);

    clear_buffer(value->item, value->size);

    if (matches_empty_string(entry->item))
    {
        return;
    }

    char starts_with_delimiter = *entry->item == delimiter;

    if (starts_with_delimiter)
    {
        move_bytes(entry->item + 1, value->item, min(value->size, entry->size));
        return;
    }

    size_t delimiter_index = find_first_occurrence(entry->item, delimiter);

    if (delimiter_index == -1)
    {
        move_bytes(entry->item, key->item, min(key->size, entry->size));
        return;
    }

    char ends_with_delimiter = entry->item[delimiter_index + 1] == '\0';

    if (ends_with_delimiter)
    {
        move_bytes(entry->item, key->item, min(key->size, entry->size - 1));
        return;
    }

    move_bytes(entry->item, key->item, min(delimiter_index, key->size));

    move_bytes(entry->item + delimiter_index + 1, value->item, min(value->size, entry->size - delimiter_index - 1));
}