#include "bind_request_client.h"

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

bind_request_state_t fetch_bind_request_client_parameters(Slapi_PBlock* block, bind_request_client_t* client)
{
    if (!has_fetched_client_dn(block, client))
    {
        return CLIENT_DN_FETCH_FAILURE;
    }

    if (!has_fetched_client_roles(block, client))
    {
        return CLIENT_ROLES_FETCH_FAILURE;
    }

    if (!has_fetched_client_groups(block, client))
    {
        return CLIENT_GROUPS_FETCH_FAILURE;
    }

    if (!has_fetched_client_attributes(block, client))
    {
        return CLIENT_ATTRIBUTES_FETCH_FAILURE;
    }

    return FETCHED_PARAMETERS;
}

void dispose_bind_request_client_parameters(bind_request_client_t *client)
{
    if (!client)
    {
        return;
    }

    if (client->dn)
    {
        // TODO: Free.
    }

    if (client->roles)
    {
        // TODO: Free.
    }

    if (client->groups)
    {
        // TODO: Free.
    }

    if (client->attributes)
    {
        // TODO:: Free.
    }
}
