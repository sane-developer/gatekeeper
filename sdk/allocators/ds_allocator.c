#include "allocator.h"

void* allocate_memory(size_t size)
{
    (void) size;
    return NULL; // TODO: Implement via dirsrv API.
}

void* reallocate_memory(void* ptr, size_t size)
{
    (void) ptr;
    (void) size;
    return NULL; // TODO: Implement via dirsrv API.
}

void free_memory(void* ptr)
{
    (void) ptr;

    // TODO: Implement via dirsrv API.
}