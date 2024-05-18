#include "aci_rule_event_dispatcher.h"
#include "bind_request_event_dispatcher.h"
#include "plugin_registration_event_dispatcher.h"

void on_applied_aci_rule(applied_aci_rule_event_args_t args)
{
    // REMARK: Implement based on business requirements.
}

void on_triggered_aci_rule(triggered_aci_rule_event_args_t args)
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

void on_finished_registration(accepted_registration_event_args_t args)
{
    // REMARK: Implement based on business requirements.
}

void on_aborted_registration(aborted_registration_event_args_t args)
{
    // REMARK: Implement based on business requirements.
}
