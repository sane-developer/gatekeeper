#include "flag_utils.h"

char has_flag(const int src, const int target)
{
    return (source & target) == target;
}

void set_flag(void* src, const int target)
{
    int* flags = src;

    *flags |= target;
}

void remove_flag(void* src, const int target)
{
    int* flags = source;

    *flags &= ~target;
}