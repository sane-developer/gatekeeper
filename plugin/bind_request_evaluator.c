#include "bind_request.h"

/* Available operations for DN attribute */

static bool dn_matches(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dn_equals(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dn_starts_with(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dn_ends_with(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Available operations for groups attribute */

static bool groups_all(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool groups_any(const char* source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Available operations for IP attribute */

static bool ip_between(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool ip_matches(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool ip_equals(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Available operations for DNS attribute */

static bool dns_between(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dns_matches(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool dns_equals(const PRNetAddr* source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Available operations for time attribute */

static bool time_after(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool time_before(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool time_between(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Available operations for weekday attribute */

static bool weekday_after(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool weekday_before(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool weekday_between(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

static bool weekday_equals(uint32_t source, const aci_rule_operand_t* operands)
{
    return false;
}

/* Resolvers for operations of each supported bind request attribute */

static bool satisfies_dn_operation(const char* dn, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case MATCHES:
            return dn_matches(dn, operation->operands);
        case EQUALS:
            return dn_equals(dn, operation->operands);
        case STARTS_WITH:
            return dn_starts_with(dn, operation->operands);
        case ENDS_WITH:
            return dn_ends_with(dn, operation->operands);
        default:
            return false;
    }
}

static bool satisfies_groups_operation(const char* groups, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case MATCHES:
            return groups_all(groups, operation->operands);
        case EQUALS:
            return groups_any(groups, operation->operands);
        default:
            return false;
    }
}

static bool satisfies_ip_operation(const PRNetAddr* ip, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case BETWEEN:
            return ip_between(ip, operation->operands);
        case MATCHES:
            return ip_matches(ip, operation->operands);
        case EQUALS:
            return ip_equals(ip, operation->operands);
        default:
            return false;
    }
}

static bool satisfies_dns_operation(const PRNetAddr* dns, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case BETWEEN:
            return dns_between(dns, operation->operands);
        case MATCHES:
            return dns_matches(dns, operation->operands);
        case EQUALS:
            return dns_equals(dns, operation->operands);
        default:
            return false;
    }
}

static bool satisfies_time_operation(uint32_t time, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case AFTER:
            return time_after(time, operation->operands);
        case BEFORE:
            return time_before(time, operation->operands);
        case BETWEEN:
            return time_between(time, operation->operands);
        default:
            return false;
    }
}

static bool satisfies_weekday_operation(uint32_t weekday, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case AFTER:
            return weekday_after(weekday, operation->operands);
        case BEFORE:
            return weekday_before(weekday, operation->operands);
        case BETWEEN:
            return weekday_between(weekday, operation->operands);
        case EQUALS:
            return weekday_equals(weekday, operation->operands);
        default:
            return false;
    }
}

static bool satisfies_operation_for_attribute(const bind_request_t* request, const aci_rule_operation_t* operation)
{
    switch (operation->operation_type)
    {
        case DN:
            return satisfies_dn_operation(request->dn, operation);
        case GROUP:
            return satisfies_groups_operation(request->groups, operation);
        case IP:
            return satisfies_ip_operation(request->ip, operation);
        case DNS:
            return satisfies_dns_operation(request->dns, operation);
        case TIME:
            return satisfies_time_operation(request->time, operation);
        case WEEKDAY:
            return satisfies_weekday_operation(request->weekday, operation);
        default:
            return false;
    }
}

// TODO: Implement actual evaluator.
