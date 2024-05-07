#include "plugin_registrar_actions.h"
#include "plugin_registrar_events.h"
#include "plugin_registrar_status.h"

plugin_registrar_status_t register_plugin(Slapi_PBlock* block)
{
    on_registration_success(block);

    return REGISTERED_PLUGIN;
}

plugin_registrar_status_t cancel_registration(Slapi_PBlock* block, plugin_registrar_error_t error)
{
    on_registration_failure(block, error);

    return error;
}
