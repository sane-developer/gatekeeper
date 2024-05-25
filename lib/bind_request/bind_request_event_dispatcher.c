#include "bind_request_event_dispatcher.h"
#include "bind_request_resolver.h"

void signal_granted_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    on_granted_bind_request((granted_bind_request_event_args_t) {
        .block = block,
        .request = request
    });

    dispose_bind_request_parameters(request);
}

void signal_denied_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    on_denied_bind_request((denied_bind_request_event_args_t) {
        .block = block,
        .request = request,
    });

    dispose_bind_request_parameters(request);
}

void signal_unresolved_bind_request_parameter(Slapi_PBlock* block, bind_request_resolver_error_t error)
{
    on_unresolved_bind_request_parameter((unresolved_bind_request_parameter_event_args_t) {
        .block = block,
        .error = error
    });
}
