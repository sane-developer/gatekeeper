#include "bind_request_provider.h"

static void fetch_request_time(bind_request_t* request)
{
    PRTime time = PR_Now();

    PR_ExplodeTime(time, PR_LocalTimeParameters, &request->datetime);
}

static int fetch_ldap_client_dn(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_BIND_TARGET, request->dn) == 0;
}

static int fetch_ldap_client_ip(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_CONN_CLIENTNETADDR, request->ip) == 0;
}

static int fetch_ldap_client_dns(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, request->dns) == 0;
}

static int fetch_ldap_client_roles(Slapi_PBlock* block, bind_request_t* request)
{
    return 0; // TODO: Implement.
}

static int fetch_ldap_client_groups(Slapi_PBlock* block, bind_request_t* request)
{
    return 0; // TODO: Implement.
}

static int fetch_ldap_client_attributes(Slapi_PBlock* block, bind_request_t* request)
{
    return 0; // TODO: Implement.
}

bind_request_status_t fetch_bind_request_parameters(Slapi_PBlock* block, bind_request_t* request)
{
    fetch_request_time(request);

    if (!fetch_ldap_client_dn(block, request))
    {
        return REQUEST_DN_FETCH_FAILURE;
    }

    if (!fetch_ldap_client_ip(block, request))
    {
        return REQUEST_IP_FETCH_FAILURE;
    }

    if (!fetch_ldap_client_dns(block, request))
    {
        return REQUEST_DNS_FETCH_FAILURE;
    }

    if (!fetch_ldap_client_roles(block, request))
    {
        return REQUEST_ROLES_FETCH_FAILURE;
    }

    if (!fetch_ldap_client_groups(block, request))
    {
        return REQUEST_GROUPS_FETCH_FAILURE;
    }

    if (!fetch_ldap_client_attributes(block, request))
    {
        return REQUEST_ATTRIBUTES_FETCH_FAILURE;
    }

    return REQUEST_PARAMETERS_FETCH_SUCCESS;
}

void dispose_bind_request_parameters(bind_request_t* request)
{
    if (!request)
    {
        return;
    }

    if (request->roles)
    {
        // TODO: Free.
    }

    if (request->groups)
    {
        // TODO: Free.
    }

    if (request->attributes)
    {
        // TODO: Free.
    }

    if (request->reason)
    {
        // TODO: Free.
    }
}
