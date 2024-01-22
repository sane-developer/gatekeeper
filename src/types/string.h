#ifndef GATEKEEPER_STRING_H
#define GATEKEEPER_STRING_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../allocators/allocator.h"

///
/// @brief Represents a mutable character buffer.
///
typedef struct
{
    char* item;
    size_t capacity;
}
string_t;

///
/// @brief Allocates an empty string on the heap.
/// @param capacity The capacity of the string buffer.
/// @return The allocated string when allocated successfully; otherwise, NULL.
///
string_t* string_from_size(size_t capacity);

///
/// @brief Allocates a string on the heap with contents from provided buffer.
/// @param string The string containing contents of the newly allocated string.
/// @return The allocated string when allocated successfully; otherwise, NULL.
///
string_t* string_from_string(const string_t* string);

///
/// @brief Allocates a string on the heap with contents from provided buffer.
/// @param buffer The contents of the newly allocated string.
/// @return The allocated string when allocated successfully; otherwise, NULL.
///
string_t* string_from_string_literal(const char* buffer);

///
/// @brief Frees the contents of the string and the string itself.
/// @param string The string to free.
///
void dispose_string(string_t* string);

///
/// @brief Clears the contents of the string.
/// @param string The string to clear.
/// @return 1 when the string has been successfully cleared; otherwise, 0.
///
char clear_contents_of(const string_t* string);

///
/// @brief Determines whether the string is empty.
/// @param string The string in question.
/// @return 1 when the string is empty; otherwise, 0.
/// @remark 1 is also returned in case the string or its buffer is NULL.
///
char is_empty(const string_t* string);

///
/// @brief Determines whether the strings are equal.
/// @param left The first string.
/// @param right The second string.
/// @return 1 when the contents of both strings are equal; otherwise 0.
/// @remark 0 is also returned in case any of the strings or its buffer is NULL.
///
char matches_contents_of_string(const string_t* left, const string_t* right);

///
/// @brief Determines whether the strings are equal.
/// @param left The string.
/// @param right The string literal.
/// @return 1 when the contents of both strings are equal; otherwise 0.
/// @remark 0 is also returned in case the string or any of the buffers is NULL.
///
char matches_contents_of_string_literal(const string_t* left, const char* right);

///
/// @brief Moves the contents of one string to another.
/// @param src The source of the contents.
/// @param dst The receiver of the contents.
/// @return 1 when the contents have been successfully yoinked; otherwise, 0.
/// @remark In case any of the strings or its buffer is NULL the operation is cancelled.
/// @remark In case the moved contents are larger than the receiver's buffer capacity they will be trimmed to fit in.
///
char yoink_contents_from_string(const string_t* src, string_t* dst);

///
/// @brief Moves the contents of one string to another.
/// @param src The source of the contents.
/// @param dst The receiver of the contents.
/// @return 1 when the contents have been successfully yoinked; otherwise, 0.
/// @remark In case any of the strings or its buffer is NULL the operation is cancelled.
/// @remark In case the moved contents are larger than the receiver's buffer capacity they will be trimmed to fit in.
///
char yoink_contents_from_string_literal(const char* src, string_t* dst);

///
/// @brief Removes all whitespaces from the string.
/// @param src The source of the contents to condense.
/// @param dst The receiver of the condensed contents.
/// @return 1 when the whitespaces have been successfully erased; otherwise, 0.
/// @remark In case any of the strings or its buffer is NULL the operation is cancelled.
/// @remark In case the moved contents are larger than the receiver's buffer capacity they will be trimmed to fit in.
///
char erase_whitespaces_from_string(const string_t* src, string_t* dst);

///
/// @brief Removes all whitespaces from the string literal.
/// @param src The source of the contents to condense.
/// @param dst The receiver of the condensed contents.
/// @return 1 when the whitespaces have been successfully erased; otherwise, 0.
/// @remark In case any of the strings or its buffer is NULL the operation is cancelled.
/// @remark In case the moved contents are larger than the receiver's buffer capacity they will be trimmed to fit in.
///
char erase_whitespaces_from_string_literal(const char* src, string_t* dst);

#endif