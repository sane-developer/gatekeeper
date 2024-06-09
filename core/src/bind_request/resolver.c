#include "bind_request.h"

static void dispose_bind_request(bind_request_t* request)
{
    if (request->groups)
    {
        slapi_ch_array_free(request->groups);
    }
}

static bool has_resolved_client_dn(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_BIND_TARGET, request->dn) == 0;
}

static bool has_resolved_client_ip(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_CONN_CLIENTNETADDR, request->ip) == 0;
}

static bool has_resolved_client_dns(Slapi_PBlock* block, bind_request_t* request)
{
    return slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, request->dns) == 0;
}

static bool has_resolved_client_groups(Slapi_PBlock* block, bind_request_t* request, Slapi_ComponentId* identity)
{
    Slapi_Entry* user_entry;

    Slapi_DN* user_dn = slapi_sdn_new_dn_byval(request->dn);

    char* attributes[] = { "memberOf", NULL };

    int code = slapi_search_internal_get_entry(user_dn, attributes, &user_entry, identity);

    if (code != LDAP_SUCCESS)
    {
        slapi_sdn_free(&user_dn);

        return false;
    }

    char** groups = slapi_entry_attr_get_charray(user_entry, "memberOf");

    if (!groups)
    {
        slapi_sdn_free(&user_dn);

        slapi_entry_free(user_entry);

        return false;
    }

    slapi_sdn_free(&user_dn);

    slapi_entry_free(user_entry);

    request->groups = groups;

    return true;
}

static void resolve_request_datetime(bind_request_t* request)
{
    PRExplodedTime datetime;

    PRTime time = PR_Now();

    PR_ExplodeTime(time, PR_LocalTimeParameters, &datetime);

    request->time = datetime.tm_hour * 100 + datetime.tm_min;

    request->weekday = datetime.tm_wday;
}

bool has_resolved_bind_request(Slapi_PBlock* block, bind_request_t* request, Slapi_ComponentId* identity)
{
    if (!has_resolved_client_dn(block, request))
    {
        on_bind_request_unresolved((on_bind_request_unresolved_event_args_t) {
            .block = block,
            .request = request,
            .error = REQUEST_DN_UNRESOLVED
        });

        return false;
    }

    if (!has_resolved_client_ip(block, request))
    {
        on_bind_request_unresolved((on_bind_request_unresolved_event_args_t) {
            .block = block,
            .request = request,
            .error = REQUEST_IP_UNRESOLVED
        });

        return false;
    }

    if (!has_resolved_client_dns(block, request))
    {
        on_bind_request_unresolved((on_bind_request_unresolved_event_args_t) {
            .block = block,
            .request = request,
            .error = REQUEST_DNS_UNRESOLVED
        });

        return false;
    }

    if (!has_resolved_client_groups(block, request, identity))
    {
        on_bind_request_unresolved((on_bind_request_unresolved_event_args_t) {
            .block = block,
            .request = request,
            .error = REQUEST_GROUPS_UNRESOLVED
        });

        return false;
    }

    resolve_request_datetime(request);

    return true;
}

bind_request_status_t grant_bind_request(bind_request_t* request)
{
    dispose_bind_request(request);

    return REQUEST_GRANTED;
}

bind_request_status_t deny_bind_request(bind_request_t* request)
{
    dispose_bind_request(request);

    return REQUEST_DENIED;
}
