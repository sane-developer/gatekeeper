#ifndef GATEKEEPER_ALLOCATOR_H
#define GATEKEEPER_ALLOCATOR_H

#include <stddef.h>

///
/// @brief Allocates the memory chunk of requested size.
/// @param size The size of the memory chunk.
/// @returns The pointer to the allocated memory block.
///
void* allocate_memory(size_t size);

///
/// @brief Frees the allocated memory.
/// @param ptr The pointer to the allocated memory.
///
void free_memory(void* ptr);

#endif
