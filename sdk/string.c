#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "string_t.h"
#include "allocator.h"

#define SIZE sizeof(string_t)

string_t* string_from_size(size_t size)
{
    string_t* string = (string_t*) allocate_memory(SIZE);

    const size_t capacity = size + 1;

    string->value = (char*) allocate_memory(capacity);

    memset(string->value, 0, capacity);

    string->value[0] = '\0';

    string->size = capacity;

    return string;
}

string_t* string_from_literal(const char* contents)
{
    string_t* string = (string_t*) allocate_memory(SIZE);

    const size_t capacity = strlen(contents) + 1;

    string->value = (char*) allocate_memory(capacity);

    const size_t length = capacity - 1;

    memcpy(string->value, contents, length);

    string->value[length] = '\0';

    string->size = capacity;

    return string;
}

void dispose_string(string_t* string)
{
    free_memory(string->value);
    
    free_memory(string);
}

void append_to_string(string_t* string, const char* format, ...)
{
    va_list args;

    va_start(args, format);

    char buffer[string->size];

    vsprintf(buffer, format, args);

    size_t offset = strlen(string->value);
    
    size_t length = strlen(buffer);

    memmove(string->value + offset, buffer, length);

    string->value[offset + length] = '\0';

    va_end(args);
}
