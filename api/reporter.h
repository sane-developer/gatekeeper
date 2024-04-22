#ifndef GATEKEEPER_REPORTER_H_
#define GATEKEEPER_REPORTER_H_

#include "bind_request.h"

///
/// @brief Reports a granted LDAP bind request via specified medium.
/// @param request Pointer to a populated bind_request_t variable.
///
void report_granted_request(const bind_request_t* const request);

///
/// @brief Reports a denied LDAP bind request via specified medium.
/// @param request Pointer to a populated bind_request_t variable.
///
void report_denied_request(const bind_request_t* const request);

#endif  // GATEKEEPER_REPORTER_H_
