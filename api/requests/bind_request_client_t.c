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

static int set_client_dn(const Slapi_PBlock* const block, bind_request_client_t* const client)
{
    return 1;
}

static int set_client_ip(const Slapi_PBlock* const block, bind_request_client_t* const client)
{
    return 1;
}

static int set_client_dns(const Slapi_PBlock* const block, bind_request_client_t* const client)
{
    return 1;
}

static int set_client_auth(const Slapi_PBlock* const block, bind_request_client_t* const client)
{
    return 1;
}

int initialize_bind_request_client(const Slapi_PBlock* const block, bind_request_client_t* const client)
{
    if (!set_client_dn(block, client))
    {
        return 0;
    }

    if (!set_client_ip(block, client))
    {
        return 0;
    }

    if (!set_client_dns(block, client))
    {
        return 0;
    }

    if (!set_client_auth(block, client))
    {
        return 0;
    }

    return 1;
}

void dispose_bind_request_client(bind_request_client_t* client)
{
    (void) client;
}
