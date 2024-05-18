#ifndef ACI_RULE_EVENT_DISPATCHER_H
#define ACI_RULE_EVENT_DISPATCHER_H

#include <dirsrv/slapi-plugin.h>

typedef struct
{
    Slapi_PBlock* block;

    char* rule_label;
}
applied_aci_rule_event_args_t;

typedef struct
{
    Slapi_PBlock* block;

    char* rule_label;

    char* condition_label;
}
triggered_aci_rule_event_args_t;

void on_applied_aci_rule(
    applied_aci_rule_event_args_t args
);

void on_triggered_aci_rule(
    triggered_aci_rule_event_args_t args
);

#endif  // ACI_RULE_EVENT_DISPATCHER_H
