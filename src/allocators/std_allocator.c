#include <assert.h>
#include <stdlib.h>
#include "allocator.h"

void* allocate_memory(size_t size)
{
    assert(size > 0 && "Cannot allocate block of size 0.");

    void* block = malloc(size);

    assert(block != NULL && "Could not allocate memory block of requested size.");

    return block;
}

void free_memory(void *ptr)
{
    assert(ptr != NULL && "Trying to free unallocated resource.");

    free(ptr);
}