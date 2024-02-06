#include "flags.h"

char has_flag(int src, int target)
{
    return (src & target) == target;
}

void enable_flag(void* src, int target)
{
    int* flags = src;

    *flags |= target;
}

void disable_flag(void* src, int target)
{
    int* flags = src;

    *flags &= ~target;
}