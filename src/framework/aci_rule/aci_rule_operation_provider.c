#include "aci_rule_operation_provider.h"

aci_rule_operation_t get_operation(aci_rule_resource_type_t parameter, aci_rule_operation_type_t operation)
{
    switch (parameter)
    {
        case DN:
            return get_dn_operation(operation);
        case IP:
            return get_ip_operation(operation);
        case DNS:
            return get_dns_operation(operation);
        case ROLES:
            return get_roles_operation(operation);
        case GROUPS:
            return get_groups_operation(operation);
        case ATTRIBUTES:
            return get_attributes_operation(operation);
        case DAY_OF_WEEK:
            return get_day_of_week_operation(operation);
        case TIME_OF_DAY:
            return get_time_of_day_operation(operation);
    }
}
