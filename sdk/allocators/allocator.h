#ifndef GATEKEEPER_ALLOCATOR_H
#define GATEKEEPER_ALLOCATOR_H

#include <stddef.h>

///
/// @brief Allocates a memory block of the specified size on the heap.
/// @param size The size of the new memory block.
/// @return The pointer to the newly allocated memory block.
///
void* allocate_memory(size_t size);

///
/// @brief Reallocates a memory block to the specified size.
/// @param ptr The memory block to reallocate.
/// @param size The size of the new memory block.
/// @return The pointer to the reallocated memory block.
///
void* reallocate_memory(void* ptr, size_t size);

///
/// @brief Frees a memory block from the heap.
/// @param ptr The pointer to the memory block to dispose.
///
void free_memory(void* ptr);

#endif // GATEKEEPER_ALLOCATOR_H