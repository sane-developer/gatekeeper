#include "bind_request_t.h"

int initialize_bind_request(Slapi_PBlock* block, bind_request_t* const request)
{
    bind_request_datetime_t datetime = {0};

    initialize_bind_request_datetime(&datetime); 

    bind_request_client_t client = {0};

    if (!initialize_bind_request_client(block, &client))
    {
        dispose_bind_request_client(&client);
        return 0;
    }

    *request->client = (bind_request_client_t)
    {
        .dn = client.dn,
        .ip = client.ip,
        .dns = client.dns,
        .auth = client.auth
    };

    *request->datetime = (bind_request_datetime_t)
    {
        .full_date = datetime.full_date,
        .day_of_week = datetime.day_of_week,
        .time_of_day = datetime.time_of_day
    };

    return 1;
}

void dispose_bind_request(bind_request_t* request)
{
    if (!request)
    {
        return;
    }

    if (request->client)
    {
        dispose_bind_request_client(request->client);
    }
}
