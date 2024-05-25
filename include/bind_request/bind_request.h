#ifndef BIND_REQUEST_H
#define BIND_REQUEST_H

#include <nspr4/prio.h>

typedef struct
{
    char* dn;

    PRNetAddr* ip;

    PRNetAddr* dns;

    char* groups;

    char* attributes;

    PRExplodedTime datetime;

    char* reason;
}
bind_request_t;

#endif  // BIND_REQUEST_H
