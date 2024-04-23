#include "bind_request.h"

static int has_fetched_client_dn(Slapi_PBlock* block, bind_request_client_t* client)
{
    return slapi_pblock_get(block, SLAPI_BIND_TARGET, client->dn) != 0;
}

static int has_fetched_client_roles(Slapi_PBlock* block, bind_request_client_t* client)
{
    return 0; // TODO: Implement LDAP client roles fetching. 
}

static int has_fetched_client_groups(Slapi_PBlock* block, bind_request_client_t* client)
{
    return 0; // TODO: Implement LDAP client groups fetching.
}

static int has_fetched_client_attributes(Slapi_PBlock* block, bind_request_client_t* client)
{
    return 0; // TODO: Implement LDAP client attributes fetching.
}

static int has_fetched_client_ip(Slapi_PBlock* block, bind_request_connection_t* connection)
{
    return slapi_pblock_get(block, SLAPI_CONN_CLIENTNETADDR, connection->ip) != 0;
}

static int has_fetched_client_dns(Slapi_PBlock* block, bind_request_connection_t* connection)
{
    return slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, connection->dns) != 0;
}

static int has_fetched_client_auth(Slapi_PBlock* block, bind_request_connection_t* connection)
{
    return 1;
}

bind_request_state_t fetch_bind_request_parameters(Slapi_PBlock* block, bind_request_t* const request)
{
    bind_request_client_t client = {0};

    if (!has_fetched_client_dn(block, &client))
    {
        return CLIENT_DN_FETCH_FAILURE;
    }

    if (!has_fetched_client_roles(block, &client))
    {
        return CLIENT_ROLES_FETCH_FAILURE;
    }

    if (!has_fetched_client_groups(block, &client))
    {
        return CLIENT_GROUPS_FETCH_FAILURE;
    }

    if (!has_fetched_client_attributes(block, &client))
    {
        return CLIENT_ATTRIBUTES_FETCH_FAILURE;
    }

    bind_request_connection_t connection = {0};

    if (!has_fetched_client_ip(block, &connection))
    {
        return CLIENT_IP_FETCH_FAILURE;
    }

    if (!has_fetched_client_dns(block, &connection))
    {
        return CLIENT_DNS_FETCH_FAILURE;
    }

    if (!has_fetched_client_auth(block, &connection))
    {
        return CLIENT_AUTH_FETCH_FAILURE;
    }

    time_t timer = time(NULL);

    *request->client = (bind_request_client_t)
    {
        .dn = client.dn,
        .roles = client.roles,
        .groups = client.groups,
        .attributes = client.attributes
    };

    *request->connection = (bind_request_connection_t)
    {
        .ip = connection.ip,
        .dns = connection.dns,
        .auth = connection.auth,
        .time = localtime(&timer)
    };

    return PARAMETERS_FETCH_SUCCESS;
}

bind_request_state_t grant_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    return REQUEST_GRANTED;
}

bind_request_state_t deny_bind_request(Slapi_PBlock* block, bind_request_t* request, bind_request_state_t state)
{
    return REQUEST_DENIED;
}
