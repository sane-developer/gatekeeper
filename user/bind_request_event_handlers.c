#include "bind_request_event_handlers.h"

void on_granted_bind_request(Slapi_PBlock* block, const bind_request_t* request)
{
    (void) block;
    (void) request;
}

void on_denied_bind_request(Slapi_PBlock* block, const bind_request_t* request)
{
    (void) block;
    (void) request;
}
