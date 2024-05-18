#include "aci_rule_operation_resolver.h"

aci_rule_operation_handler_t resolve_operation_for_operand(
    aci_rule_operation_type_t operation_type,
    aci_rule_operand_type_t operand_type)
{
    switch (operand_type)
    {
        case DN:
            return resolve_operation_for_dn_operand(operation_type);
        case IP:
            return resolve_operation_for_ip_operand(operation_type);
        case DNS:
            return resolve_operation_for_dns_operand(operation_type);
        case GROUP:
            return resolve_operation_for_group_operand(operation_type);
        case ATTRIBUTE:
            return resolve_operation_for_attribute_operand(operation_type);
        case WEEKDAY:
            return resolve_operation_for_weekday_operand(operation_type);
        case TIME:
            return resolve_operation_for_time_operand(operation_type);
    }
}
