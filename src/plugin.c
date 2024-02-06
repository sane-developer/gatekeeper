#include "plugin.h"

int initialize_plugin()
{
    plugin_binding_policy = supply_binding_policy(NULL);

    if (!plugin_binding_policy)
    {
        return 1;
    }

    plugin_logging_policy = supply_logging_policy(NULL);

    if (!plugin_logging_policy)
    {
        return 1;
    }

    return 0;
}

char evaluate_bind_request()
{
    return 0;
}
