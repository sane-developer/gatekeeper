#include "bind_request_datetime_t.h"
#include <time.h>

static void set_full_date(const struct tm* const local_time, bind_request_datetime_t* const datetime)
{
    (void) local_time;
    (void) datetime;
}

static void set_day_of_week(const struct tm* const local_time, bind_request_datetime_t* const datetime)
{
    (void) local_time;
    (void) datetime;
}

static void set_time_of_day(const struct tm* const local_time, bind_request_datetime_t* const datetime)
{
    (void) local_time;
    (void) datetime;
}

void initialize_bind_request_datetime(bind_request_datetime_t* const datetime)
{
    time_t timer = time(NULL);

    struct tm* local_time = localtime(&timer);

    set_full_date(local_time, datetime);

    set_day_of_week(local_time, datetime);

    set_time_of_day(local_time, datetime);
}
