#ifndef PLUGIN_REGISTRATION_EVENT_DISPATCHER_H
#define PLUGIN_REGISTRATION_EVENT_DISPATCHER_H

#include <dirsrv/slapi-plugin.h>
#include "plugin_registration_errors.h"
#include "plugin_registration_status.h"

typedef struct
{
    Slapi_PBlock* block;
}
accepted_registration_event_args_t;

typedef struct
{
    Slapi_PBlock* block;

    plugin_registration_error_t error;
}
aborted_registration_event_args_t;

void on_accepted_registration(
    accepted_registration_event_args_t args
);

void on_aborted_registration(
    aborted_registration_event_args_t args
);

plugin_registration_status_t signal_accepted_registration(
    Slapi_PBlock* block
);

plugin_registration_status_t signal_aborted_registration(
    Slapi_PBlock* block,
    plugin_registration_error_t error
);

#endif  // PLUGIN_REGISTRATION_EVENT_DISPATCHER_H