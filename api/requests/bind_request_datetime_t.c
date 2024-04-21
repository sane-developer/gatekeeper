#include "bind_request_datetime_t.h"

int set_full_date(const struct tm* local_time, char* full_date)
{
    return 1;
}

int set_day_of_week(const struct tm* local_time, uint32_t* day_of_week)
{
    return 1;
}

int set_time_of_day(const struct tm* local_time, uint32_t* time_of_day)
{
    return 1;
}
