#include "plugin.h"

void on_plugin_registration_finished(on_plugin_registration_finished_event_args_t args)
{
    // Ignore.
}

void on_plugin_registration_aborted(on_plugin_registration_aborted_event_args_t args)
{
    // Ignore.
}

void on_bind_request_unresolved(on_bind_request_unresolved_event_args_t args)
{
    // Ignore.
}

void on_bind_request_granted(on_bind_request_granted_event_args_t args)
{
    // Ignore.
}

void on_bind_request_denied(on_bind_request_denied_event_args_t args)
{
    printf("Reason: Triggered '%s' rule.\n", args.violated_rule_label);

    printf("Details: Triggered '%s' condition.\n", args.violated_condition_label);
}
