#ifndef GATEKEEPER_ALLOCATOR_H_
#define GATEKEEPER_ALLOCATOR_H_

#include <stddef.h>

///
/// @brief Allocates a memory chunk of size of the specified type.
/// @param type The type of a memory chunk.
/// @return A pointer to newly allocated memory chunk of size of the specified type.
///
#define allocate_memory_of_type(type) allocate_memory(sizeof(type))

///
/// @brief Allocates a memory chunk of the specified size.
/// @param size The size of a memory chunk.
/// @return A pointer to newly allocated memory chunk of specified size.
///
void* allocate_memory(size_t size);

#endif  // GATEKEEPER_ALLOCATOR_H_
