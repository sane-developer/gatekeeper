#include "bind_request.h"

int get_request_details(const Slapi_PBlock* block, bind_request_t* request)
{
    return 0;
}

int has_applied_rule(const bind_request_t* request, const binding_rule_t* rule)
{
    return 0;
}

int has_met_rule_conditions(const bind_request_t* request, const binding_rule_t* rule)
{
    return 0;
}

void log_bind_request(logging_strategy_t strategy, const bind_request_t* request)
{
    
}
