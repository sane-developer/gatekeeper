#include "bind_request_connection.h"

static int has_fetched_connection_ip(Slapi_PBlock* block, bind_request_connection_t* connection)
{
    return slapi_pblock_get(block, SLAPI_CONN_CLIENTNETADDR, connection->ip) != 0;
}

static int has_fetched_connection_dns(Slapi_PBlock* block, bind_request_connection_t* connection)
{
    return slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, connection->dns) != 0;
}

static int has_fetched_connection_auth(Slapi_PBlock* block, bind_request_connection_t* connection)
{
    return 1; // TODO: Implement.
}

static int has_fetched_connection_time(bind_request_connection_t* connection)
{
    time_t timer = time(NULL);

    connection->time = localtime(&timer);

    return 1;
}

bind_request_state_t fetch_bind_request_connection_parameters(Slapi_PBlock* block, bind_request_connection_t* connection)
{
    if (!has_fetched_connection_ip(block, connection))
    {
        return CONNECTION_IP_FETCH_FAILURE;
    }

    if (!has_fetched_connection_dns(block, connection))
    {
        return CONNECTION_DNS_FETCH_FAILURE;
    }

    if (!has_fetched_connection_auth(block, connection))
    {
        return CONNECTION_AUTH_FETCH_FAILURE;
    }

    if (!has_fetched_connection_time(connection))
    {
        return CONNECTION_TIME_FETCH_FAILURE;
    }

    return FETCHED_PARAMETERS;
}

void dispose_bind_request_connection_parameters(bind_request_connection_t* connection)
{
    if (!connection)
    {
        return;
    }

    if (connection->ip)
    {
        // TODO: Free.
    }

    if (connection->dns)
    {
        // TODO: Free.
    }
}
