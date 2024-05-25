#include "plugin_registration_event_dispatcher.h"

plugin_registration_status_t signal_accepted_registration(Slapi_PBlock* block)
{
    on_accepted_registration((accepted_registration_event_args_t) {
        .block = block
    });

    return REGISTRATION_ACCEPTED;
}

plugin_registration_status_t signal_aborted_registration(Slapi_PBlock* block, plugin_registration_error_t error)
{
    on_aborted_registration((aborted_registration_event_args_t) {
        .block = block,
        .error = error
    });

    return REGISTRATION_ABORTED;
}
