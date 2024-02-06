#include <assert.h>
#include "array.h"
#include "../allocators/allocator.h"

void* array_from_size(size_t capacity, size_t item_size)
{
    assert(capacity != 0 && "The capacity of an array must be larger than 0.");
    assert(item_size != 0 && "The item size of an array must be larger than 0.");

    array_t* array = allocate_memory(sizeof(array_t));

    array->items = allocate_memory(capacity * item_size);
    array->capacity = capacity;
    array->count = 0;

    return array;
}

void dispose_complex_array(void* array, cleanup_array_internals cleanup)
{
    assert(array && "The array was NULL.");

    array_t* root = array;

    for (size_t index = 0; index < root->count; index++)
    {
        void* item = root->items[index];

        if (cleanup != NULL)
        {
            cleanup(item);
        }

        free_memory(item);
    }

    free_memory(root);
}

void dispose_simple_array(void* array)
{
    dispose_complex_array(array, NULL);
}

void append_item(void* array, void* item)
{
    assert(array && "The array was NULL.");
    assert(item && "The item was NULL.");

    array_t* root = array;

    if (root->count == root->capacity)
    {
        return; // TODO: Resize.
    }

    root->items[root->count] = item;
    root->count++;
}