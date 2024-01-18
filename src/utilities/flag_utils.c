#include "flag_utils.h"

char has_flag(const int source, const int target)
{
    return (source & target) == target;
}

void set_flag(void* source, const int target)
{
    int* container = source;

    *container |= target;
}

void remove_flag(void* source, const int target)
{
    int* container = source;

    *container &= ~target;
}