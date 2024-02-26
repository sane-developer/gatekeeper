#include <stdlib.h>
#include "../allocators/allocator.h"
#include "../loggers/logger.h"

void* allocate_memory(size_t size)
{
    if (size == 0)
    {
        log_critical("Attempted to allocate 0 bytes.");
    
        exit(1);
    }

    void* memory = malloc(size);
    
    if (memory == NULL)
    {
        log_critical("Could not allocate requested memory chunk (%zu bytes).", size);
        
        exit(1);
    }

    return memory; 
}

void* reallocate_memory(void* ptr, size_t size)
{
    if (ptr == NULL)
    {
        log_critical("Attempted to reallocate NULL pointer.");

        exit(1);
    }

    if (size == 0)
    {
        log_critical("Attempted to allocate 0 bytes.");
    
        exit(1);
    }

    return realloc(ptr, size); 
}

void free_memory(void* ptr)
{
    if (ptr == NULL)
    {
        log_critical("Attempted to free NULL pointer.");
        
        exit(1);
    }

    free(ptr);
}
