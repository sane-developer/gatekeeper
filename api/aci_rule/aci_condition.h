#ifndef ACI_CONDITION_H_
#define ACI_CONDITION_H_

#include <stddef.h>

typedef enum
{
    DN,
    IP,
    DNS,
    AUTH,
    ROLES,
    GROUPS,
    ATTRIBUTES,
    DAY_OF_WEEK,
    TIME_OF_DAY
}
aci_condition_parameter_t;

typedef enum
{
    MATCHES = 1 << 0,
    EQUALS = 1 << 1,
    EXCEPT = 1 << 2,
    ANY = 1 << 3
}
aci_condition_operation_t;

const aci_condition_operation_t allowed_operations[9] =
{
    [DN] = MATCHES | EQUALS | EXCEPT | ANY,    
    [IP] = 0,
    [DNS] = 0,
    [AUTH] = 0,
    [ROLES] = 0,
    [GROUPS] = 0,
    [ATTRIBUTES] = 0,
    [DAY_OF_WEEK] = 0,
    [TIME_OF_DAY] = 0
};

typedef struct
{
    char** items;
    
    size_t capacity;
    
    size_t count;
}
aci_condition_t;

typedef struct
{
    aci_condition_t** items;
    
    size_t capacity;
    
    size_t count;
}
aci_conditions_t;


#endif  // ACI_CONDITION_H_
