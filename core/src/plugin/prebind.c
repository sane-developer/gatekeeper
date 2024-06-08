#include "plugin.h"

static bind_request_status_t grant_bind_request(bind_request_t* request)
{
    dispose_bind_request(request);

    return REQUEST_GRANTED;
}

static bind_request_status_t deny_bind_request(bind_request_t* request)
{
    dispose_bind_request(request);

    return REQUEST_DENIED;
}

bind_request_status_t handle_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    if (!has_resolved_bind_request(block, &request))
    {
        return deny_bind_request(&request);
    }

    if (has_triggered_any_deny_rule(block, &request, &plugin_deny_aci_rules))
    {
        return deny_bind_request(&request);
    }

    if (has_triggered_any_grant_rule(block, &request, &plugin_grant_aci_rules))
    {
        return deny_bind_request(&request);
    }

    return grant_bind_request(&request);
}
