#include <assert.h>
#include "array.h"
#include "../allocators/allocator.h"

void* array_from_size(size_t capacity)
{
    assert(capacity != 0 && "The capacity of an array must be larger than 0.");

    const size_t array_size = sizeof(array_t);

    const size_t item_size = sizeof(void*);

    array_t* array = allocate_memory(array_size);

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

void* get_item_from_array(void* array, size_t index)
{
    assert(array && "The array was NULL.");

    array_t* root = array;

    assert(root->capacity >= index);

    return root->items[index];
}

void* get_last_item_from_array(void* array)
{
    assert(array && "The array was NULL.");

    array_t* root = array;

    if (root->count == 0)
    {
        return NULL;
    }

    return root->items[root->count - 1];
}

void append_item_to_array(void* array, void* item)
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