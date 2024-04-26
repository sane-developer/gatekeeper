#ifndef PLUGIN_H_
#define PLUGIN_H_

#include "aci_rule.h"
#include "bind_request.h"

///
/// @brief Collection of custom ACI rules of grant type.
///
static aci_rules_t* grant_aci_rules;

///
/// @brief Collection of custom ACI rules of deny type.
///
static aci_rules_t* deny_aci_rules;

///
/// @brief Identity of the plugin.
///
static Slapi_ComponentId* plugin_id;

///
/// @brief Metadata of the plugin.
///
static Slapi_PluginDesc plugin_desc = (Slapi_PluginDesc)
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Evaluates the bind request against custom-made ACI rules."
};

///
/// @brief Represents the possible state of plugin registration process.
///
typedef enum
{
    ///
    /// @brief Value indicating that directory server registered the plugin successfully.
    ///
    REGISTRATION_SUCCESS = 0,

    ///
    /// @brief Value indicating that directory server failed to retrieve the plugin identity.
    ///
    FAILED_TO_GET_PLUGIN_IDENTITY = 1,

    ///
    /// @brief Value indicating that directory server failed to set the plugin metadata.
    ///
    FAILED_TO_SET_PLUGIN_DESCRIPTION = 2,

    ///
    /// @brief Value indicating that directory server failed to set the LDAP protocol version.
    ///
    FAILED_TO_SET_LDAP_PROTOCOL_VERSION = 3,

    ///
    /// @brief Value indicating that directory server failed to set the bind request evaluation handler.
    ///
    FAILED_TO_SET_BIND_REQUEST_HANDLER = 4,

    ///
    /// @brief Value indicating that custom ACI rules parser returned an error.
    ///
    FAILED_TO_SUPPLY_CUSTOM_ACI_RULES = 5
}
plugin_registration_state_t;

///
/// @brief Handles the incoming bind request issued by the LDAP client.
/// @param block Pointer to operation parameters retrieved from the directory server.
/// @return
///     - REQUEST_GRANTED, when the bind request satisfied all of the applied custom ACI rules.
///     - REQUEST_DENIED, otherwise.
///
bind_request_state_t on_recieved_bind_request(Slapi_PBlock* block);

///
/// @brief Handles the bind request that has been granted.
/// @param block Pointer to Slapi_PBlock variable that contains the operation parameters retrieved from the directory server.
/// @param request Pointer to bind_request_t variable that contains the metadata of the LDAP client, connection, local time.
/// @return REQUEST_GRANTED.
///
bind_request_state_t on_granted_bind_request(Slapi_PBlock* block, bind_request_t* request);

///
/// @brief Handles the bind request that has been denied.
/// @param block Pointer to operation parameters retrieved from the directory server.
/// @param request Pointer to bind_request_t variable that contains the metadata of the LDAP client, connection, local time.
/// @param error Numerical representation of the error that caused the denial of bind request.
/// @return REQUEST_DENIED.
///
bind_request_state_t on_denied_bind_request(Slapi_PBlock* block, bind_request_t* request, bind_request_state_t error);

///
/// @brief Handles the successful plugin registration.
/// @param success Numerical representation of the plugin registration success state.
/// @return REGISTRATION_SUCCESS.
///
plugin_registration_state_t on_registration_success(plugin_registration_state_t success);

///
/// @brief Handles the unsuccessful plugin registration.
/// @param error Numerical representation of the state that caused the plugin registration failure.
/// @return
///     - FAILED_TO_GET_PLUGIN_IDENTITY, when the directory server could not retrieve the plugin identity.
///     - FAILED_TO_SET_PLUGIN_DESCRIPTION, when the directory server could not set the plugin metadata.
///     - FAILED_TO_SET_LDAP_PROTOCOL_VERSION, when the directory server could not set the LDAP protocol version.
///     - FAILED_TO_SET_BIND_REQUEST_HANDLER, when the directory server could not set the bind request handler.
///     - FAILED_TO_SET_CUSTOM_ACI_RULES, when the custom ACI rules parser returned an error.
///
plugin_registration_state_t on_registration_failure(plugin_registration_state_t error);

#endif // PLUGIN_H_
