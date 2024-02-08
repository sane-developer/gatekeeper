#include "xf_binding_policy_parser.h"

xf_bpp_output_t parse_binding_policy(const xf_bpp_args_t* args)
{
    (void) args;

    return (xf_bpp_output_t)
    {
        .temp = (void*) 0
    };
}

char validate_binding_policy(const xf_bpv_args_t* args)
{
    (void) args;

    return 0;
}