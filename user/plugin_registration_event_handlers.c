#include "plugin_registration_event_handlers.h"

void on_plugin_registration_success(Slapi_PBlock* block)
{
    (void) block;
}

void on_plugin_registration_failure(Slapi_PBlock* block, plugin_registration_error_t error)
{
    (void) block;
    (void) error;
}
