#include <stdlib.h>
#include "allocator.h"

void* allocate_memory(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }

    return malloc(size);
}

void free_memory(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    free(ptr);
}