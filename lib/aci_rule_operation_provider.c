#include "aci_rule_operation_provider.h"

aci_rule_operation_t get_operation_for_operand(aci_rule_operand_type_t operand, aci_rule_operation_type_t operation)
{
    switch (operand)
    {
        case DN:
            return get_operation_for_dn_operand(operation);
        case IP:
            return get_operation_for_ip_operand(operation);
        case DNS:
            return get_operation_for_dns_operand(operation);
        case ROLE:
            return get_operation_for_role_operand(operation);
        case GROUP:
            return get_operation_for_group_operand(operation);
        case ATTRIBUTE:
            return get_operation_for_attribute_operand(operation);
        case WEEKDAY:
            return get_operation_for_weekday_operand(operation);
        case TIME:
            return get_operation_for_time_operand(operation);
    }
}
