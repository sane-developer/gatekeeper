#include "bind_request_resolver.h"

bool fetch_client_dn(Slapi_PBlock* block, char* dn)
{
    return slapi_pblock_get(block, SLAPI_BIND_TARGET, dn) == 0;
}

bool fetch_client_ip(Slapi_PBlock* block, PRNetAddr* ip)
{
    return slapi_pblock_get(block, SLAPI_CONN_CLIENTNETADDR, ip) == 0;
}

bool fetch_client_dns(Slapi_PBlock* block, PRNetAddr* dns)
{
    return slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, dns) == 0;
}

bool fetch_client_groups(Slapi_PBlock* block, char* groups)
{
    return false; // TODO: Fetch.
}

bool fetch_client_attributes(Slapi_PBlock* block, char* attributes)
{
    return false; // TODO: Fetch.
}

void fetch_request_datetime(PRExplodedTime* datetime)
{
    PRTime now = PR_Now();

    PR_ExplodeTime(now, PR_LocalTimeParameters, datetime);
}

void dispose_bind_request_parameters(bind_request_t* request)
{
    if (request->groups)
    {
        slapi_ch_free_string(&request->groups);
    }

    if (request->attributes)
    {
        slapi_ch_free_string(&request->attributes);
    }
}
