#ifndef PLUGIN_REGISTRATION_STATUS_H
#define PLUGIN_REGISTRATION_STATUS_H

///
/// @brief
///
typedef enum
{
    ///
    /// @brief
    ///
    REGISTERED_PLUGIN = 0,

    ///
    /// @brief
    ///
    FAILED_TO_GET_PLUGIN_IDENTITY,

    ///
    /// @brief
    ///
    FAILED_TO_SET_PLUGIN_DESCRIPTION,

    ///
    /// @brief
    ///
    FAILED_TO_SET_PLUGIN_LDAP_PROTOCOL_VERSION,

    ///
    /// @brief
    ///
    FAILED_TO_SET_PLUGIN_BIND_REQUEST_HANDLER,

    ///
    /// @brief
    ///
    FAILED_TO_SET_PLUGIN_BIND_POLICY
}
plugin_registration_status_t, plugin_registration_error_t;

#endif  // PLUGIN_REGISTRATION_STATUS_H
