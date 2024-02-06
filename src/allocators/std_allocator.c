#include <assert.h>
#include <stdlib.h>
#include "allocator.h"

void* allocate_memory(size_t size)
{
    assert(size > 0 && "Memory block size must be larger than 0.");

    void* block = malloc(size);

    assert(block && "Could not allocate memory block of requested size.");

    return block;
}

void free_memory(void *ptr)
{
    assert(ptr && "Attempted to free a NULL pointer.");

    free(ptr);
}