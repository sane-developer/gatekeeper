#ifndef GATEKEEPER_BIND_REQUEST_T_H_
#define GATEKEEPER_BIND_REQUEST_T_H_

#include "bind_request_client_t.h"
#include "bind_request_datetime_t.h"

///
/// @brief Represents the bind request issued by the LDAP client.
///
typedef struct
{
    ///
    /// @brief Pointer to the LDAP client metadata retrieved from the directory server.
    ///
    bind_request_client_t* client;

    ///
    /// @brief Pointer to the date & time metadata retrieved from the system.
    ///
    bind_request_datetime_t* datetime;
}
bind_request_t;

///
/// @brief Attempt to initialize bind request metadata.
/// @param block Pointer to a key-value pair storage for bind operation parameters.
/// @param request Pointer to a zeroed bind_request_t variable.
/// @return
///     - 1, when all of the fields were successfully initialized.
///     - 0, when any of the fields could not be initialized.
///
int initialize_bind_request(Slapi_PBlock* block, bind_request_t* const request);

///
/// @brief Disposes metadata inside bind_request_t variable.
/// @param client Pointer to a populated bind_request_t variable.
///
void dispose_bind_request(bind_request_t* request);

#endif  // GATEKEEPER_BIND_REQUEST_T_H_
