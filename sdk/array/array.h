#ifndef GATEKEEPER_ARRAY_H
#define GATEKEEPER_ARRAY_H

#include <stddef.h>

///
/// @brief Represents a mutable dynamic array.
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
#define append(array, item) append_item_to_array((array), (item))

///
/// @brief
/// @param array
/// @param item
///
void append_item_to_array(array_t* array, void* item);



#endif // GATEKEEPER_ARRAY_H