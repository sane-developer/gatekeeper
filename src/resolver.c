#include "bind_request.h"

static bool resolve_client_dn(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_BIND_TARGET, request->dn) == 0;
}

static bool resolve_client_ip(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_CONN_CLIENTNETADDR, request->ip) == 0;
}

static bool resolve_client_dns(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, request->dns) == 0;
}

static bool resolve_client_groups(Slapi_PBlock* block, bind_request_t* request)
{
    return true; // TODO: Resolve LDAP client groups.
}

static void resolve_request_datetime(bind_request_t* request)
{
    PRExplodedTime datetime;

    PRTime time = PR_Now();

    PR_ExplodeTime(time, PR_LocalTimeParameters, &datetime);

    request->time = datetime.tm_hour * 100 + datetime.tm_min;

    request->weekday = datetime.tm_wday;
}

bind_request_status_t resolve_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    if (!resolve_client_dn(block, request))
    {
        return REQUEST_DN_UNRESOLVED;
    }

    if (!resolve_client_ip(block, request))
    {
        return REQUEST_IP_UNRESOLVED;
    }

    if (!resolve_client_dns(block, request))
    {
        return REQUEST_DNS_UNRESOLVED;
    }

    if (!resolve_client_groups(block, request))
    {
        return REQUEST_GROUPS_UNRESOLVED;
    }

    resolve_request_datetime(request);

    return REQUEST_RESOLVED;
}

void dispose_bind_request(bind_request_t* request)
{
    if (request->groups)
    {
        slapi_ch_free_string(&request->groups);
    }
}
