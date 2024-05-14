#include "plugin.h"
#include "bind_policy_provider.h"
#include "bind_request_evaluator.h"
#include "bind_request_initializer.h"
#include "bind_request_event_handlers.h"
#include "plugin_registration_event_handlers.h"

static bind_request_status_t grant_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    on_granted_bind_request(block, request);

    dispose_request_parameters(request);

    return REQUEST_GRANTED;
}

static bind_request_status_t deny_bind_request(Slapi_PBlock* block, bind_request_t* request)
{
    on_denied_bind_request(block, request);

    dispose_request_parameters(request);

    return REQUEST_DENIED;
}

static bind_request_status_t evaluate_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    if (!has_fetched_request_parameters(block, &request))
    {
        return deny_bind_request(block, &request);
    }

    if (!has_satisfied_deny_rules(policy.deny_rules, &request))
    {
        return deny_bind_request(block, &request);
    }

    if (!has_satisfied_grant_rules(policy.grant_rules, &request))
    {
        return deny_bind_request(block, &request);
    }

    return grant_bind_request(block, &request);
}

static bool get_plugin_identity(Slapi_PBlock* block)
{
    return slapi_pblock_get(block, SLAPI_PLUGIN_IDENTITY, identity) == 0;
}

static bool set_plugin_description(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_DESCRIPTION, &description) == 0;
}

static bool set_plugin_ldap_protocol_version(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_VERSION, SLAPI_PLUGIN_VERSION_03) == 0;
}

static bool set_plugin_bind_request_handler(Slapi_PBlock* block)
{
    return slapi_pblock_set(block, SLAPI_PLUGIN_PRE_BIND_FN, evaluate_bind_request) == 0;
}

static plugin_registration_status_t cancel_registration(Slapi_PBlock* block, plugin_registration_error_t error)
{
    on_plugin_registration_failure(block, error);

    return error;
}

static plugin_registration_status_t finish_registration(Slapi_PBlock* block)
{
    on_plugin_registration_success(block);

    return REGISTERED_PLUGIN;
}

plugin_registration_status_t register_plugin(Slapi_PBlock* block)
{
    if (!get_plugin_identity(block))
    {
        return cancel_registration(block, FAILED_TO_GET_PLUGIN_IDENTITY);
    }

    if (!set_plugin_description(block))
    {
        return cancel_registration(block, FAILED_TO_SET_PLUGIN_DESCRIPTION);
    }

    if (!set_plugin_ldap_protocol_version(block))
    {
        return cancel_registration(block, FAILED_TO_SET_PLUGIN_LDAP_PROTOCOL_VERSION);
    }

    if (!set_plugin_bind_request_handler(block))
    {
        return cancel_registration(block, FAILED_TO_SET_PLUGIN_BIND_REQUEST_HANDLER);
    }

    if (!set_plugin_bind_policy(block, &policy))
    {
        return cancel_registration(block, FAILED_TO_SET_PLUGIN_BIND_POLICY);
    }

    return finish_registration(block);
}
