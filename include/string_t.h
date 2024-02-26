#ifndef GATEKEEPER_STRING_H
#define GATEKEEPER_STRING_H

#include <stddef.h>

///
/// @brief Represents a mutable character span.
///
typedef struct
{
    char* value;
    size_t size;
}
string_t;

///
/// @brief
/// @param size
/// @return 
///
string_t* string_from_size(size_t size);

///
/// @brief
/// @param contents
/// @return
///
string_t* string_from_literal(const char* contents);

///
/// @brief
/// @param string
///
void dispose_string(string_t* string);

///
/// @brief
/// @param string
/// @param format
/// @param ...
///
void append_to_string(string_t* string, const char* format, ...);

#endif // GATEKEEPER_STRING_H
