#ifndef BIND_REQUEST_EVENTS_H_
#define BIND_REQUEST_EVENTS_H_

#include "bind_request.h"

///
/// @brief Handles a granted bind request.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @param request Pointer to a bind_request_t variable that stores the LDAP client and connection parameters.
/// @return REQUEST_GRANTED.
///
bind_request_status_t on_granted_bind_request(Slapi_PBlock* block, bind_request_t* request);

///
/// @brief Handles a denied bind request.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @param request Pointer to a bind_request_t variable that stores the LDAP client and connection parameters.
/// @param error Numerical representation of error which caused the bind request to be denied.
/// @return REQUEST_DENIED.
///
bind_request_status_t on_denied_bind_request(Slapi_PBlock* block, bind_request_t* request, bind_request_status_t error);

#endif  // BIND_REQUEST_EVENTS_H_
