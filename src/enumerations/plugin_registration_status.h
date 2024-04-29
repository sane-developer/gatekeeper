#ifndef PLUGIN_REGISTRATION_STATUS_H_
#define PLUGIN_REGISTRATION_STATUS_H_

///
/// @brief Represents the statuses of each plugin registration step.
///
typedef enum
{
    ///
    /// @brief Value indicating that plugin has been successfully registered.
    ///
    SUCCESSFULLY_REGISTERED = 0,
    
    ///
    /// @brief Value indicating that an error has occured while getting the plugin identity.
    ///
    FAILED_TO_GET_PLUGIN_IDENTITY = 1,
    
    ///
    /// @brief Value indicating that an error has occured while setting the plugin API version.
    ///
    FAILED_TO_SET_PLUGIN_API_VERSION = 2,
    
    ///
    /// @brief Value indicating that an error has occured while setting the plugin description.
    ///
    FAILED_TO_SET_PLUGIN_DESCRIPTION = 3,
    
    ///
    /// @brief Value indicating that an error has occured while setting the bind request handler.
    ///
    FAILED_TO_SET_PLUGIN_BIND_REQUEST_HANDLER = 4,
    
    ///
    /// @brief Value indicating that an error has occured while parsing the ACI rules.
    ///
    FAILED_TO_PARSE_CUSTOM_ACI_RULES = 5
}
plugin_registration_status_t;

#endif  // PLUGIN_REGISTRATION_STATUS_H_
