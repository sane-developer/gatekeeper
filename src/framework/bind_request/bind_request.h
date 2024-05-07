#ifndef GATEKEEPER_BIND_REQUEST_T_H
#define GATEKEEPER_BIND_REQUEST_T_H

#include <nspr4/prio.h>

typedef struct
{
    char* dn;

    PRNetAddr* ip;

    PRNetAddr* dns;

    char** roles;

    char** groups;

    char** attributes;

    PRExplodedTime datetime;

    char* reason;
}
bind_request_t;

#endif  // GATEKEEPER_BIND_REQUEST_T_H
