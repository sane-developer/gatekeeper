#ifndef ACI_RULE_OPERATION_RESOLVER_H
#define ACI_RULE_OPERATION_RESOLVER_H

#include "aci_rule_operation.h"
#include "bind_request.h"
#include <stdbool.h>

typedef bool (*aci_rule_operation_handler_t)(aci_rule_operand_t*, bind_request_t*);

aci_rule_operation_handler_t resolve_operation_for_operand(
    aci_rule_operation_type_t operation_type,
    aci_rule_operand_type_t operand_type
);

aci_rule_operation_handler_t resolve_operation_for_dn_operand(
    aci_rule_operation_type_t operation_type
);

aci_rule_operation_handler_t resolve_operation_for_ip_operand(
    aci_rule_operation_type_t operation_type
);

aci_rule_operation_handler_t resolve_operation_for_dns_operand(
    aci_rule_operation_type_t operation_type
);

aci_rule_operation_handler_t resolve_operation_for_group_operand(
    aci_rule_operation_type_t operation_type
);

aci_rule_operation_handler_t resolve_operation_for_attribute_operand(
    aci_rule_operation_type_t operation_type
);

aci_rule_operation_handler_t resolve_operation_for_weekday_operand(
    aci_rule_operation_type_t operation_type
);

aci_rule_operation_handler_t resolve_operation_for_time_operand(
    aci_rule_operation_type_t operation_type
);

#endif  // ACI_RULE_OPERATION_RESOLVER_H
