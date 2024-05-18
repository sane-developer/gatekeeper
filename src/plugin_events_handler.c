#include "bind_request_evaluator.h"
#include "bind_request_resolver.h"
#include "plugin_bootstrapper.h"

void on_finished_registration(finished_registration_event_args_t args)
{
    // REMARK: Implement based on business requirements.
}

void on_aborted_registration(aborted_registration_event_args_t args)
{
    // REMARK: Implement based on business requirements.
}

void on_granted_bind_request(granted_bind_request_event_args_t args)
{
    // REMARK: Implement based on business requirements.
}

void on_denied_bind_request(denied_bind_request_event_args_t args)
{
    // REMARK: Implement based on business requirements.
}

void on_unresolved_bind_request_parameter(unresolved_bind_request_parameter_event_args_t args)
{
    // REMARK: Implement based on business requirements.
}
