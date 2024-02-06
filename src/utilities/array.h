#ifndef GATEKEEPER_ARRAY_H
#define GATEKEEPER_ARRAY_H

#include <stddef.h>

///
/// @brief Represents a generic mutable dynamic array.
///
typedef struct
{
    void** items;
    size_t capacity;
    size_t count;
}
array_t;

///
/// @brief
///
typedef void (*cleanup_array_internals)(void* item);

///
/// @brief
/// @param capacity
/// @param item_size
/// @return
///
void* array_from_size(size_t capacity, size_t item_size);

///
/// @brief
/// @param array
/// @param cleanup
///
void dispose_complex_array(void* array, cleanup_array_internals cleanup);

///
/// @brief
/// @param array
///
void dispose_simple_array(void* array);

///
/// @brief
/// @param array
/// @param item
///
void append_item(void* array, void* item);

#endif