#ifndef GATEKEEPER_STRING_UTILS_H
#define GATEKEEPER_STRING_UTILS_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

///
/// @brief Represents a character buffer.
///
typedef struct
{
    ///
    /// @brief The pointer to the allocated buffer.
    ///
    char* item;

    ///
    /// @brief The size of the allocated buffer.
    ///
    size_t size;
}
string_t;

///
/// @brief Determines which of two integers is smaller.
/// @param x The first integer.
/// @param y The second integer.
/// @return The smaller of two integers.
/// @remark Please future me, use it just for integers.
///
#define min(x, y) (x) > (y) ? (y) : (x)

///
/// @brief Determines whether the string is empty.
/// @param src The string to verify.
///
#define matches_empty_string(src) (src)[0] == '\0'

///
/// @brief Determines whether the strings are equal.
/// @param lb The first string.
/// @param rb The second string.
///
#define matches_string(lb, rb) strcmp((lb), (rb)) == 0

///
/// @brief Erases the contents of the buffer.
/// @param src The buffer to clear.
/// @param size The size of the buffer.
///
#define clear_buffer(src, size) memset((src), 0, (size)); (src)[(size)] = '\0'

///
/// @brief Moves specified amount of bytes from one buffer to another.
/// @param from The source of bytes to move.
/// @param to The destination for the content.
/// @param count The total count of bytes to move.
///
#define move_bytes(from, to, count) memmove((to), (from), (count))

///
/// @brief Allocates the string, clears its content.
/// @param string The string to allocate.
/// @param size The size of the string.
///
#define initialize_empty_string(src, size) initialize_string((src), (size), NULL)

///
/// @brief Allocates the string, clears its content, and sets the content.
/// @param string The string to allocate.
/// @param size The size of the string.
/// @param content The content of the allocated string.
///
void initialize_string(string_t* src, size_t size, const char* content);

///
/// @brief Deallocates the string item and sets the size to 0.
/// @param string The string to dispose.
///
void dispose_string(string_t* src);

///
/// @brief Determines whether the string is made of digits only.
/// @param src The string to verify.
/// @return 1 when the string contains only digits; otherwise, 0.
///
char is_number(const char* src);

///
/// @brief Converts the string into respective integer.
/// @param src The string to convert.
/// @param dst The pointer to the allocated integer.
/// @return 1 when the string has been successfully converted; otherwise, 0.
/// @remark The string must be made of digits specifically.
///
char convert_string_to_integer(const char* src, int* dst);

///
/// @brief Erases every whitespace character from the string.
/// @param src The string to process.
/// @param dst The container for processed string.
///
void erase_whitespaces_from_string(const char* src, char* dst);

///
/// @brief Extracts a key-value pair from the string.
/// @param src The pointer to a buffer containing the key-value pair.
/// @param key The pointer to a key buffer to populate.
/// @param value The pointer to a value buffer to populate.
/// @param delimiter The character dividing the key-value pair.
///
void extract_key_value_pair_from_string(const string_t* src, string_t* key, string_t* value, char delimiter);

#endif
