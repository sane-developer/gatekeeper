#ifndef GATEKEEPER_REPORTER_H_
#define GATEKEEPER_REPORTER_H_

#include "bind_request_t.h"

///
/// @brief Reports a granted LDAP bind request via specified medium.
/// @param request Pointer to a populated bind_request_t variable.
/// @param response Pointer to a populated bind_response_t variable.
///
void report_granted_request(
    const bind_request_t* const request, 
    const void* const response
);

///
/// @brief Reports a denied LDAP bind request via specified medium.
/// @param request Pointer to a populated bind_request_t variable.
/// @param response Pointer to a populated bind_response_t variable.
///
void report_denied_request(
    const bind_request_t* const request, 
    const void* const response
);

#endif  // GATEKEEPER_REPORTER_H_
