#include "bind_request_initializer.h"

static bool has_fetched_client_dn(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_BIND_TARGET, request->dn) == 0;
}

static bool has_fetched_client_ip(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_CONN_CLIENTNETADDR, request->ip) == 0;
}

static bool has_fetched_client_dns(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, request->dns) == 0;
}

static bool has_fetched_client_roles(Slapi_PBlock* block, bind_request_t* request)
{
    return false; // TODO: Fetch.
}

static bool has_fetched_client_groups(Slapi_PBlock* block, bind_request_t* request)
{
    return false; // TODO: Fetch.
}

static bool has_fetched_client_attributes(Slapi_PBlock* block, bind_request_t* request)
{
    return false; // TODO: Fetch.
}

static void fetch_request_weekday_and_time(bind_request_t* request)
{
    PRTime time = PR_Now();

    PR_ExplodeTime(time, PR_LocalTimeParameters, &request->datetime);
}

bool has_fetched_request_parameters(Slapi_PBlock* block, bind_request_t* request)
{
    fetch_request_weekday_and_time(request);

    if (!has_fetched_client_dn(block, request))
    {
        request->status = FAILED_TO_FETCH_CLIENT_DN;

        return false;
    }

    if (!has_fetched_client_ip(block, request))
    {
        request->status = FAILED_TO_FETCH_CLIENT_IP;

        return false;
    }

    if (!has_fetched_client_dns(block, request))
    {
        request->status = FAILED_TO_FETCH_CLIENT_DNS;

        return false;
    }

    if (!has_fetched_client_roles(block, request))
    {
        request->status = FAILED_TO_FETCH_CLIENT_ROLES;

        return false;
    }

    if (!has_fetched_client_groups(block, request))
    {
        request->status = FAILED_TO_FETCH_CLIENT_GROUPS;

        return false;
    }

    if (!has_fetched_client_attributes(block, request))
    {
        request->status = FAILED_TO_FETCH_CLIENT_ATTRIBUTES;

        return false;
    }

    return true;
}

void dispose_request_parameters(bind_request_t* request)
{
    if (request->roles)
    {
        slapi_ch_free_string(&request->roles);
    }

    if (request->groups)
    {
        slapi_ch_free_string(&request->groups);
    }

    if (request->attributes)
    {
        slapi_ch_free_string(&request->attributes);
    }

    if (request->reason)
    {
        slapi_ch_free_string(&request->reason);
    }
}
