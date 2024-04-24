#ifndef GATEKEEPER_REPORTER_H_
#define GATEKEEPER_REPORTER_H_

#include "bind_request.h"

///
/// @brief Reports a granted LDAP bind request via specified medium.
/// @param block Pointer to operation parameters retrieved from the directory server.
/// @param request Pointer to bind_request_t variable that contains the metadata of the LDAP client, connection, local time.
///
void report_granted_bind_request(Slapi_PBlock* block, const bind_request_t* request);

///
/// @brief Reports a denied LDAP bind request via specified medium.
/// @param block Pointer to operation parameters retrieved from the directory server.
/// @param request Pointer to bind_request_t variable that contains the metadata of the LDAP client, connection, local time.
/// @param error Numerical representation of the error that caused the denial of bind request.
///
void report_denied_bind_request(Slapi_PBlock* block, const bind_request_t* request, bind_request_state_t error);

#endif  // GATEKEEPER_REPORTER_H_
