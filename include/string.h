#ifndef GATEKEEPER_STRING_H
#define GATEKEEPER_STRING_H

///
/// @brief Represents a mutable character span.
///
typedef struct
{
    char* value;
    size_t size;
}
string_t;

#endif // GATEKEEPER_STRING_H