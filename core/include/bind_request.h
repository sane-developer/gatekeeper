#ifndef BIND_REQUEST_H
#define BIND_REQUEST_H

#include "bind_policy.h"

///
/// @brief
///
typedef enum
{
    REQUEST_GRANTED = 0,

    REQUEST_DENIED = 1,

    REQUEST_RESOLVED,

    REQUEST_DN_UNRESOLVED,

    REQUEST_IP_UNRESOLVED,

    REQUEST_DNS_UNRESOLVED,

    REQUEST_GROUPS_UNRESOLVED,

    REQUEST_SATISFIED_GRANT_RULES,

    REQUEST_SATISFIED_DENY_RULES,

    REQUEST_VIOLATED_RULE
}
bind_request_status_t;

///
/// @brief
///
typedef struct
{
    char* dn;

    char* groups;

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

    bind_request_t* request;

    bind_request_status_t error;
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
/// @return
///
bind_request_status_t has_resolved_bind_request(Slapi_PBlock* block, bind_request_t* request);

///
/// @brief
/// @param request
///
void dispose_bind_request(bind_request_t* request);

///
/// @brief
/// @param block
/// @param request
/// @param policy
/// @return
///
bool has_triggered_any_grant_rule(Slapi_PBlock* block, const bind_request_t* request, const bind_policy_t* policy);

///
/// @brief
/// @param block
/// @param request
/// @param policy
/// @return
///
bool has_triggered_any_deny_rule(Slapi_PBlock* block, const bind_request_t* request, const bind_policy_t* policy);

#endif  // BIND_REQUEST_H
