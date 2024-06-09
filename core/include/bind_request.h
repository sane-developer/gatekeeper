#ifndef BIND_REQUEST_H
#define BIND_REQUEST_H

#include "aci_rule.h"
#include <dirsrv/slapi-plugin.h>

///
/// @brief
///
typedef enum
{
    REQUEST_GRANTED = 0,

    REQUEST_DENIED = 1,

    REQUEST_DN_UNRESOLVED,

    REQUEST_IP_UNRESOLVED,

    REQUEST_DNS_UNRESOLVED,

    REQUEST_GROUPS_UNRESOLVED
}
bind_request_status_t;

///
/// @brief
///
typedef struct
{
    char* dn;

    char** groups;

    PRNetAddr* ip;

    PRNetAddr* dns;

    uint32_t time;

    uint32_t weekday;
}
bind_request_t;

///
/// @brief
///
typedef struct
{
    Slapi_PBlock* block;

    const bind_request_t* request;
}
on_bind_request_granted_event_args_t;

///
/// @brief
///
typedef struct
{
    Slapi_PBlock* block;

    const bind_request_t* request;

    const char* violated_rule_label;

    const char* violated_condition_label;
}
on_bind_request_denied_event_args_t;

///
/// @brief
///
typedef struct
{
    Slapi_PBlock* block;

    const bind_request_t* request;

    const bind_request_status_t error;
}
on_bind_request_unresolved_event_args_t;

///
/// @brief
/// @param args
///
void on_bind_request_granted(on_bind_request_granted_event_args_t args);

///
/// @brief
/// @param args
///
void on_bind_request_denied(on_bind_request_denied_event_args_t args);

///
/// @brief
/// @param args
///
void on_bind_request_unresolved(on_bind_request_unresolved_event_args_t args);

///
/// @brief
/// @param block
/// @param request
/// @param identity
/// @return
///
bool has_resolved_bind_request(Slapi_PBlock* block, bind_request_t* request, Slapi_ComponentId* identity);

///
/// @brief
/// @param block
/// @param request
/// @param rules
/// @return
///
bool has_triggered_any_special_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rules_t* rules);

///
/// @brief
/// @param block
/// @param request
/// @param rules
/// @return
///
bool has_triggered_any_grant_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rules_t* rules);

///
/// @brief
/// @param block
/// @param request
/// @param rules
/// @return
///
bool has_triggered_any_deny_rule(Slapi_PBlock* block, const bind_request_t* request, const aci_rules_t* rules);

///
/// @brief
/// @param request
/// @return
///
bind_request_status_t grant_bind_request(bind_request_t* request);

///
/// @brief
/// @param request
/// @return
///
bind_request_status_t deny_bind_request(bind_request_t* request);

#endif  // BIND_REQUEST_H
