#ifndef PLUGIN_REGISTRAR_STATUS_T_H
#define PLUGIN_REGISTRAR_STATUS_T_H

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
    FAILED_TO_SET_PLUGIN_CUSTOM_ACI_RULES
}
plugin_registrar_status_t, plugin_registrar_error_t;

#endif  // PLUGIN_REGISTRAR_STATUS_T_H
