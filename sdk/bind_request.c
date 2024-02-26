#include "flags.h"
#include "logger.h"
#include "string_t.h"
#include "bind_request_t.h"
#include "binding_policy_t.h"
#include "logging_policy_t.h"

static inline int respects_user_dn_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_user_ip_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_user_role_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_user_group_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_user_attrs_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_dns_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_day_of_week_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_time_of_day_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_authentication_method_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    
}

static inline int respects_filter(const bind_request_t* request, const binding_rule_filter_t* filter)
{
    switch (filter->type) 
    {
        case user_dn_filter:
            return respects_user_dn_filter(request, filter);
        case user_ip_filter: 
            return respects_user_ip_filter(request, filter);
        case user_role_filter:
            return respects_user_role_filter(request, filter);
        case user_group_filter:
            return respects_user_group_filter(request, filter);
        case user_attributes_filter:
            return respects_user_attrs_filter(request, filter);
        case dns_filter:
            return respects_dns_filter(request, filter);
        case day_of_week_filter:
            return respects_day_of_week_filter(request, filter);
        case time_of_day_filter:
            return respects_time_of_day_filter(request, filter);
        case authentication_method_filter:
            return respects_authentication_method_filter(request, filter);
        default:
            return 0; 
    }
}

int get_request_details(Slapi_PBlock* block, bind_request_t* request)
{
    if (slapi_pblock_get(block, SLAPI_BIND_TARGET, request->client_dn) != 0)
    {
        return 0;
    }

    if (slapi_pblock_get(block, SLAPI_BIND_METHOD, &request->auth_method) != 0)
    {
        return 0;
    }

    if (slapi_pblock_get(block, SLAPI_BIND_SASLMECHANISM, &request->sasl_mechanism) != 0) 
    {
        return 0;
    }

    if (slapi_pblock_get(block, SLAPI_CONN_IS_SSL_SESSION, &request->uses_ssl) != 0) 
    {
        return 0;
    }

    if (slapi_pblock_get(block, SLAPI_OPINITIATED_TIME, &request->time) != 0) 
    {
        return 0;
    }

    if (slapi_pblock_get(block, SLAPI_CONN_SERVERNETADDR, &request->server_ip) != 0) 
    {
        return 0;
    }

    return 1;
}

int has_applied_rule(const bind_request_t* request, const binding_rule_t* rule)
{
    for (size_t index = 0; index < rule->apply_filters->count; ++index)
    {
        const binding_rule_filter_t* filter = rule->apply_filters->items[index];
        
        if (!respects_filter(request, filter))
        {
            return 0;
        }
    }

    return 1;
}

int has_met_rule_conditions(const bind_request_t* request, const binding_rule_t* rule)
{
    for (size_t index = 0; index < rule->authorize_filters->count; ++index)
    {
        const binding_rule_filter_t* filter = rule->authorize_filters->items[index];
        
        if (!respects_filter(request, filter))
        {
            return 0;
        }
    }

    return 1;
}

void log_bind_request(const bind_request_t* request, logging_strategy_t strategy)
{
    string_t* buffer = string_from_size(2048);

    if (has_flag(strategy, include_user_dn))
    {
        append_to_string(buffer, "user_dn: %s\n", request->client_dn);
    }

    if (has_flag(strategy, include_user_ip))
    {
        append_to_string(buffer, "user_ip: %s\n", request->client_ip);
    }

    if (has_flag(strategy, include_user_role))
    {
        // TODO: append_to_string(buffer, "user_role: %s\n", request->client_role);
    }

    if (has_flag(strategy, include_user_group))
    {
        // TODO: append_to_string(buffer, "user_group: %s\n", request->client_group);
    }

    if (has_flag(strategy, include_evaluation))
    {
        append_to_string(buffer, "evaluation: %s\n", request->client_dn);
    }

    if (has_flag(strategy, include_date))
    {
        append_to_string(buffer, "date: %s\n", request->client_dn);
    }

    if (has_flag(strategy, include_sasl_method))
    {
        append_to_string(buffer, "sasl: %s\n", request->sasl_mechanism);
    }

    if (has_flag(strategy, include_authentication_method))
    {
        switch (request->auth_method)
        {
            case LDAP_AUTH_SIMPLE:
                append_to_string(buffer, "auth: Simple\n");
                break;
            case LDAP_AUTH_SASL:
                append_to_string(buffer, "auth: SASL\n");
                break;
            case LDAP_AUTH_KRBV4:
                append_to_string(buffer, "auth: KRBv4\n");
                break;
            case LDAP_AUTH_KRBV41:
                append_to_string(buffer, "auth: KRBv41\n");
                break;
            case LDAP_AUTH_KRBV42:
                append_to_string(buffer, "auth: KRBv42\n");
                break;
            case LDAP_AUTH_NEGOTIATE:
                append_to_string(buffer, "auth: Negotiate\n");
                break;
            case LDAP_AUTH_NONE:
                append_to_string(buffer, "auth: None\n");
                break;
            default:
                append_to_string(buffer, "auth: Unknown\n");
                break;
        }
    }

    log_info("%s\n", buffer);

    dispose_string(buffer);
}
