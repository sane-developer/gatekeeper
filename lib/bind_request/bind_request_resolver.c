#include "bind_request_resolver.h"

static bool fetch_client_dn(Slapi_PBlock* block, char* dn)
{
    return slapi_pblock_get(block, SLAPI_BIND_TARGET, dn) == 0;
}

static bool fetch_client_ip(Slapi_PBlock* block, PRNetAddr* ip)
{
    return slapi_pblock_get(block, SLAPI_CONN_CLIENTNETADDR, ip) == 0;
}

static bool fetch_client_dns(Slapi_PBlock* block, PRNetAddr* dns)
{
    return slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, dns) == 0;
}

static bool fetch_client_groups(Slapi_PBlock* block, char* groups)
{
    return false; // TODO: Fetch.
}

static bool fetch_client_attributes(Slapi_PBlock* block, char* attributes)
{
    return false; // TODO: Fetch.
}

static void fetch_request_datetime(PRExplodedTime* datetime)
{
    PRTime now = PR_Now();

    PR_ExplodeTime(now, PR_LocalTimeParameters, datetime);
}

static bool signal_unresolved_bind_request_parameter(Slapi_PBlock* block, bind_request_resolver_error_t error)
{
    on_unresolved_bind_request_parameter((unresolved_bind_request_parameter_event_args_t) {
        .block = block,
        .error = error
    });

    return false;
}

bool has_resolved_bind_request_parameters(Slapi_PBlock* block, bind_request_t* request)
{
    if (!fetch_client_dn(block, request->dn))
    {
        return signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_DN);
    }

    if (!fetch_client_ip(block, request->ip))
    {
        return signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_IP);
    }

    if (!fetch_client_dns(block, request->dns))
    {
        return signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_DNS);
    }

    if (!fetch_client_groups(block, request->groups))
    {
        return signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_GROUPS);
    }

    if (!fetch_client_attributes(block, request->attributes))
    {
        return signal_unresolved_bind_request_parameter(block, FAILED_TO_RESOLVE_CLIENT_ATTRIBUTES);
    }

    fetch_request_datetime(&request->datetime);

    return true;
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
