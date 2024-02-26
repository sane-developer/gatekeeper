#include "plugin.h"

int initialize_plugin(Slapi_PBlock* block)
{
    if (slapi_pblock_get(block, SLAPI_PLUGIN_IDENTITY, &plugin_id) != 0)
    {
        log_critical("Failed at getting plugin's identity.");
        
        return 1;
    }

    if (slapi_pblock_set(block, SLAPI_PLUGIN_VERSION, SLAPI_PLUGIN_VERSION_03) != 0)
    {
        log_critical("Failed at setting plugin version.");
        
        return 1;
    }
    
    if (slapi_pblock_set(block, SLAPI_PLUGIN_DESCRIPTION, &plugin_description) != 0)
    {
        log_critical("Failed at setting plugin description.");
        
        return 1;
    }

    if (slapi_pblock_set(block, SLAPI_PLUGIN_PRE_BIND_FN, evaluate_bind_request) != 0)
    {
        log_critical("Failed at setting bind request evaluation function.");
        
        return 1;
    }

    log_info("Successfully initialized gatekeeper plugin.");
    
    return 0;
}

int evaluate_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    if (!get_request_details(block, &request))
    {
        log_warning("Denied access due to connection data retrieval failure.");
        
        return 1;
    }

    for (size_t index = 0; index < plugin_binding_policy->deny_rules->count; ++index)
    {
        const binding_rule_t* deny_rule = plugin_binding_policy->deny_rules->items[index];

        if (has_applied_rule(&request, deny_rule))
        {
            if (has_met_rule_conditions(&request, deny_rule))
            {
                log_bind_request(&request, plugin_logging_policy->denied_requests);
                
                return 1;
            }
        }
    }

    for (size_t index = 0; index < plugin_binding_policy->allow_rules->count; ++index)
    {
        const binding_rule_t* allow_rule = plugin_binding_policy->allow_rules->items[index];

        if (has_applied_rule(&request, allow_rule))
        {
            if (!has_met_rule_conditions(&request, allow_rule))
            {
                log_bind_request(&request, plugin_logging_policy->denied_requests);
                
                return 1;
            }
        }
    }

    log_bind_request(&request, plugin_logging_policy->accepted_requests);
    
    return 0;
}
