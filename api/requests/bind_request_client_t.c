#include "bind_request_client_t.h"

static const char stringified_auth_methods[6][16] =
{
    [SSL] = "ssl",
    [NONE] = "none",
    [SIMPLE] = "simple",
    [SASL_GSSAPI] = "sasl gssapi",
    [SASL_EXTERNAL] = "sasl external",
    [SASL_DIGEST_MD5] = "sasl digest-md5"
};

int set_client_dn(Slapi_PBlock* block, char* dn)
{
    return 1;
}

int set_client_ip(Slapi_PBlock* block, uint32_t* ip)
{
    return 1;
}

int set_client_dns(Slapi_PBlock* block, uint32_t* dns)
{
    return 1;
}

int set_client_auth(Slapi_PBlock* block, authentication_method_t* auth)
{
    return 1;
}
