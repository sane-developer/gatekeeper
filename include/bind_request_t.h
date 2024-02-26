#ifndef GATEKEEPER_BIND_REQUEST_H
#define GATEKEEPER_BIND_REQUEST_H

#include <dirsrv/slapi-plugin.h>
#include <time.h>
#include "binding_policy_t.h"
#include "logging_policy_t.h"
#include "logger.h"

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
    time_t time;
}
bind_request_t;

///
/// @brief
/// @param block
/// @param request
/// @return
///
int get_request_details(Slapi_PBlock* block, bind_request_t* request);

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
/// @param request
/// @param strategy
///
void log_bind_request(const bind_request_t* request, logging_strategy_t strategy);

#endif //GATEKEEPER_BIND_REQUEST_H
