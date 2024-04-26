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

bind_request_state_t fetch_bind_request_parameters(Slapi_PBlock* block, bind_request_t* const request)
{
    bind_request_client_t client = {0};

    bind_request_state_t state_after_fetching_client_metadata = fetch_bind_request_client_parameters(block, &client);

    if (state_after_fetching_client_metadata != FETCHED_PARAMETERS)
    {
        return state_after_fetching_client_metadata;
    }

    bind_request_connection_t connection = {0};

    bind_request_state_t state_after_fetching_connection_metadata = fetch_bind_request_connection_parameters(block, &connection);

    if (state_after_fetching_connection_metadata != FETCHED_PARAMETERS)
    {
        return state_after_fetching_connection_metadata;
    }

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
        .time = connection.time 
    };

    return FETCHED_PARAMETERS;
}

void dispose_bind_request_parameters(bind_request_t *request)
{
    if (!request)
    {
        return;
    }

    if (request->client)
    {
        dispose_bind_request_client_parameters(request->client);
    }

    if (request->connection)
    {
        dispose_bind_request_connection_parameters(request->connection);
    }

    if (request->note)
    {
        // TODO: Free.
    }
}
