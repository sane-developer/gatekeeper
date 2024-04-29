#ifndef ACI_RULE_CONDITION_OPERAND_H_
#define ACI_RULE_CONDITION_OPERAND_H_

#include <stddef.h>
#include "ldap_client.h"
#include "ldap_connection.h"

///
/// @brief
///
typedef union
{
    ///
    /// @brief
    ///
    ldap_client_t* client;
    
    ///
    /// @brief
    ///
    ldap_connection_t* connection;
}
aci_rule_operand_t;

///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    aci_rule_operand_t** items;
    
    ///
    /// @brief
    ///
    size_t capacity;
    
    ///
    /// @brief
    ///
    size_t count;
}
aci_rule_operands_t;

#endif  // ACI_RULE_CONDITION_OPERAND_H_
