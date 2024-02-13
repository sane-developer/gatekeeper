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
void* array_from_size(size_t capacity);

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
/// @param index
/// @return
///
void* get_item_from_array(void* array, size_t index);

///
/// @brief
/// @param array
/// @return
///
void* get_last_item_from_array(void* array);

///
/// @brief
/// @param array
/// @param item
///
void append_item_to_array(void* array, void* item);

#endif