#ifndef GATEKEEPER_BIND_REQUEST_H
#define GATEKEEPER_BIND_REQUEST_H

#include <time.h>
#include <dirsrv/slapi-plugin.h>
#include "../loggers/logger.h"
#include "../policies/binding_policy.h"
#include "../policies/logging_policy.h"

///
/// @brief 
///
typedef struct
{
    char* client_dn;
    char* client_ip;
    char* server_ip;
    char* sasl_mechanism;
    int uses_ssl;
    int auth_method;
    time_t request_time;
}
bind_request_t;

///
/// @brief
/// @param block
/// @param request
/// @return
///
int get_request_details(const Slapi_PBlock* block, bind_request_t* request);

///
/// @brief
/// @param request
/// @param rule
/// @return
///
int has_applied_rule(const bind_request_t* request, const binding_rule_t* rule);

///
/// @brief
/// @param request
/// @param rule
/// @return
///
int has_met_rule_conditions(const bind_request_t* request, const binding_rule_t* rule);

///
/// @brief
/// @param strategy
/// @param request
///
void log_bind_request(logging_strategy_t strategy, const bind_request_t* request);

#endif //GATEKEEPER_BIND_REQUEST_H
