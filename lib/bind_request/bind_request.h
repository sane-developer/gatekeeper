#ifndef BIND_REQUEST_H
#define BIND_REQUEST_H

#include <nspr4/prio.h>

typedef enum
{
    REQUEST_GRANTED = 0,

    REQUEST_DENIED = 1
}
bind_request_status_t;

typedef struct
{
    char* dn;

    PRNetAddr* ip;

    PRNetAddr* dns;

    char* groups;

    char* attributes;

    PRExplodedTime datetime;
}
bind_request_t;

#endif  // BIND_REQUEST_H
