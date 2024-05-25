#ifndef BIND_REQUEST_RESOLVER_H
#define BIND_REQUEST_RESOLVER_H

#include "bind_request.h"
#include <dirsrv/slapi-plugin.h>
#include <stdbool.h>

bool fetch_client_dn(
    Slapi_PBlock* block,
    char* dn
);

bool fetch_client_ip(
    Slapi_PBlock* block,
    PRNetAddr* ip
);

bool fetch_client_dns(
    Slapi_PBlock* block,
    PRNetAddr* dns
);

bool fetch_client_groups(
    Slapi_PBlock* block,
    char* groups
);

bool fetch_client_attributes(
    Slapi_PBlock* block,
    char* attributes
);

void fetch_request_datetime(
    PRExplodedTime* datetime
);

void dispose_bind_request_parameters(
    bind_request_t* request
);

#endif  // BIND_REQUEST_RESOLVER_H
