#ifndef BIND_REQUEST_H
#define BIND_REQUEST_H

#include <nspr4/prio.h>

///
/// @brief
///
typedef struct
{
    ///
    /// @brief
    ///
    char* dn;

    ///
    /// @brief
    ///
    PRNetAddr* ip;

    ///
    /// @brief
    ///
    PRNetAddr* dns;

    ///
    /// @brief
    ///
    char** roles;

    ///
    /// @brief
    ///
    char** groups;

    ///
    /// @brief
    ///
    char** attributes;

    ///
    /// @brief
    ///
    PRExplodedTime datetime;

    ///
    /// @brief
    ///
    char* reason;
}
bind_request_t;

#endif  // BIND_REQUEST_H
