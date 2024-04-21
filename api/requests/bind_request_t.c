#include "bind_request_t.h"

int setup_bind_request(Slapi_PBlock* block, bind_request_t* const request)
{
    char* client_dn;

    if (!set_client_dn(block, client_dn))
    {
        return 0;
    }

    uint32_t client_ip;

    if (!set_client_ip(block, &client_ip))
    {
        return 0;
    }

    uint32_t client_dns;

    if (!set_client_dns(block, &client_dns))
    {
        return 0;
    }

    authentication_method_t client_auth;

    if (!set_client_auth(block, &client_auth))
    {
        return 0;
    }

    *request->client = (bind_request_client_t)
    {
        .dn = client_dn,
        .ip = client_ip,
        .dns = client_dns,
        .auth = client_auth
    };

    time_t current_time = time(NULL);

    struct tm* local_time = localtime(&current_time);

    char* request_full_date;

    if (!set_full_date(local_time, request_full_date))
    {
        return 1;
    }

    uint32_t request_day_of_week;

    if (!set_day_of_week(local_time, &request_day_of_week))
    {
        return 0;
    }

    uint32_t request_time_of_day;

    if (!set_time_of_day(local_time, &request_time_of_day))
    {
        return 0;
    }

    *request->datetime = (bind_request_datetime_t)
    {
        .full_date = request_full_date,
        .day_of_week = request_day_of_week,
        .time_of_day = request_time_of_day
    };

    return 1;
}

void dispose_bind_request(bind_request_t* request)
{
    if (!request)
    {
        return;
    }

    if (request->client->dn)
    {
        // TODO: Free the client dn.
    }

    if (request->datetime->full_date)
    {
        // TODO: Free the full date.
    }
}
