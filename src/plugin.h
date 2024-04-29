#ifndef PLUGIN_H_
#define PLUGIN_H_

#include "aci_rule.h"
#include "plugin_registration_status.h"

///
/// @brief Pointer to a collection of custom ACI rules that determine whether bind request should be granted.
///
static aci_rules_t* grant_aci_rules;

///
/// @brief Pointer to a collection of custom ACI rules that determine whether bind request should be denied.
///
static aci_rules_t* deny_aci_rules;

///
/// @brief Pointer to a structure that stores the identity of the plugin.
///
static Slapi_ComponentId* plugin_identity;

///
/// @brief Structure that stores the metadata of the plugin.
///
static Slapi_PluginDesc plugin_description =
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Extends the ACI rules with additional properties."
};

///
/// @brief Registers the plugin within the directory server environment.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @return
///     - REGISTRATION_SUCCESS, when the plugin has been registered successfully.
///     - Respective registration error:
///         a) when plugin failed to get the identity of the plugin,
///         b) when plugin failed to set the description of the plugin,
///         c) when plugin failed to set the version of the utilized LDAP protocol,
///         d) when plugin failed to set the handler of the bind requests,
///         e) when plugin failed to parse the custom ACI rules.
///
plugin_registration_status_t register_gatekeeper(Slapi_PBlock* block);

///
/// @brief Evaluates the bind request against the custom ACI rules.
/// @param block Pointer to a Slapi_PBlock variable that stores the operands of current operation.
/// @return
///     - REQUEST_GRANTED, when the received bind request did not trigger any of the ACI rules.
///     - REQUEST_DENIED:
///         a) when plugin failed to retrieve LDAP client parameters,
///         b) when plugin failed to retrieve LDAP connection parameters,
///         c) when bind request triggered any of the deny ACI rules,
///         d) when bind request triggered any of the grant ACI rules.
///
bind_request_status_t handle_bind_request(Slapi_PBlock* block);

#endif  // PLUGIN_H_
