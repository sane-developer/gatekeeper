#ifndef GATEKEEPER_STRING_H
#define GATEKEEPER_STRING_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

///
/// @brief Represents a mutable character buffer.
///
typedef struct
{
    char* item;
    size_t size;
}
string_t;

///
/// @brief Allocates an empty string on the heap.
/// @param size The count of characters the buffer may store.
/// @return The allocated string when allocated successfully; otherwise, NULL.
///
string_t* string_from_size(size_t size);

///
/// @brief Allocates a string on the heap with contents from provided buffer.
/// @param contents The contents of the newly allocated string.
/// @return The allocated string when allocated successfully; otherwise, NULL.
///
string_t* string_from_contents(const char* contents);

///
/// @brief Frees the contents of the string and the string itself.
/// @param string The string to free.
///
void dispose_string(string_t* string);

///
/// @brief Determines whether the string is empty.
/// @param string The string in question.
/// @return 1 when the string is empty; otherwise, 0.
/// @remark 1 is also returned in case the string or its buffer is NULL.
///
int is_empty(const string_t* string);

///
/// @brief Determines whether the strings are equal.
/// @param left The first string.
/// @param right The second string.
/// @return 1 when the contents of both strings are equal; otherwise 0.
///
int matches_string(const string_t* left, const string_t* right);

///
/// @brief Determines whether the strings are equal.
/// @param left The string.
/// @param right The string literal.
/// @return 1 when the contents of both strings are equal; otherwise 0.
///
int matches_string_literal(const string_t* left, const char* right);

///
/// @brief Clears the contents of the string.
/// @param string The string to clear.
/// @return 1 when the string has been successfully cleared; otherwise, 0.
///
void remove_contents(const string_t* string);

///
/// @brief Moves the contents of one string to another.
/// @param src The source of the contents.
/// @param dst The receiver of the contents.
/// @return 1 when the contents have been successfully yoinked; otherwise, 0.
/// @remark In case any of the strings or its buffer is NULL the operation is cancelled.
/// @remark In case the moved contents are larger than the receiver's buffer capacity they will be trimmed to fit in.
///
void yoink_string(const string_t* src, string_t* dst);

///
/// @brief Moves the contents of one string to another.
/// @param src The source of the contents.
/// @param dst The receiver of the contents.
/// @return 1 when the contents have been successfully yoinked; otherwise, 0.
/// @remark In case any of the strings or its buffer is NULL the operation is cancelled.
/// @remark In case the moved contents are larger than the receiver's buffer capacity they will be trimmed to fit in.
///
void yoink_string_literal(const char* src, string_t* dst);

///
/// @brief Removes all whitespaces from the string.
/// @param src The source of the contents to condense.
/// @param dst The receiver of the condensed contents.
/// @return 1 when the whitespaces have been successfully erased; otherwise, 0.
/// @remark In case any of the strings or its buffer is NULL the operation is cancelled.
/// @remark In case the moved contents are larger than the receiver's buffer capacity they will be trimmed to fit in.
///
void erase_whitespaces_from_string(const string_t* src, string_t* dst);

///
/// @brief Removes all whitespaces from the string literal.
/// @param src The source of the contents to condense.
/// @param dst The receiver of the condensed contents.
/// @return 1 when the whitespaces have been successfully erased; otherwise, 0.
/// @remark In case any of the strings or its buffer is NULL the operation is cancelled.
/// @remark In case the moved contents are larger than the receiver's buffer capacity they will be trimmed to fit in.
///
void erase_whitespaces_from_string_literal(const char* src, string_t* dst);

///
/// @brief
/// @param src
/// @param key
/// @param value
/// @param delimiter
/// @return
///
void split_by_delimiter(const string_t* src, string_t* key, string_t* value, char delimiter);

///
/// @brief
/// @param src
/// @param values
/// @param delimiter
/// @return
///
void split_multiple_by_delimiter(const string_t* src, array_t* values, char delimiter);

#endif