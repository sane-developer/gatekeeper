#include <stdlib.h>
#include "allocator.h"

void* allocate_memory(size_t size)
{
    return malloc(size);
}

void* reallocate_memory(void* ptr, size_t size)
{
    return realloc(ptr, size);
}

void free_memory(void* ptr)
{
    free(ptr);
}