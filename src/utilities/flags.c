#include "flags.h"

char has_flag(const int src, const int target)
{
    return (src & target) == target;
}

void enable_flag(void* src, const int target)
{
    int* flags = src;

    *flags |= target;
}

void disable_flag(void* src, const int target)
{
    int* flags = src;

    *flags &= ~target;
}