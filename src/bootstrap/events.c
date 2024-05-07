#include "bind_request_events.h"
#include "plugin_registrar_events.h"

void on_registration_success(Slapi_PBlock* block)
{
    // Write your custom logic here.
}

void on_registration_failure(Slapi_PBlock* block, plugin_registrar_error_t error)
{
    // Write your custom logic here.
}

void on_granted_bind_request(Slapi_PBlock* block, const bind_request_t* request)
{
    // Write your custom logic here.
}

void on_denied_bind_request(Slapi_PBlock* block, const bind_request_t* request, bind_request_error_t error)
{
    // Write your custom logic here.
}
