#include "aci_rule.h"
#include "aci_rules_parser.h"
#include "bind_request.h"
#include "logger.h"

static aci_rules_t* grant_aci_rules;

static aci_rules_t* deny_aci_rules;

static Slapi_ComponentId* plugin_id;

static Slapi_PluginDesc plugin_desc = (Slapi_PluginDesc)
{
    .spd_id = "gatekeeper",
    .spd_vendor = "sane-developer",
    .spd_version = "1.0.0.0",
    .spd_description = "Evaluates the bind request against custom-made ACI rules."
};

static int report_plugin_registration_success()
{
    const int PLUGIN_REGISTRATION_SUCCESS = 0;

    write_info_log("%s", "Gatekeeper has been successfully registered.");

    return PLUGIN_REGISTRATION_SUCCESS;
}

static int report_plugin_registration_failure(const char* reason)
{
    const int PLUGIN_REGISTRATION_FAILURE = -1;

    write_critical_log("%s", reason);

    return PLUGIN_REGISTRATION_FAILURE;
}

static int on_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    bind_request_state_t state_after_fetching = fetch_bind_request_parameters(block, &request);

    if (state_after_fetching != PARAMETERS_FETCH_SUCCESS)
    {
        return deny_bind_request(block, &request, state_after_fetching);
    }

    bind_request_state_t state_after_deny_rules_evaluation = satisfies_deny_aci_rules(deny_aci_rules, &request);

    if (state_after_deny_rules_evaluation != SATISFIED_DENY_ACI_RULES)
    {
        return deny_bind_request(block, &request, state_after_deny_rules_evaluation);
    }

    bind_request_state_t state_after_grant_rules_evaluation = satisfies_grant_aci_rules(grant_aci_rules, &request);

    if (state_after_grant_rules_evaluation != SATISFIED_GRANT_ACI_RULES)
    {
        return deny_bind_request(block, &request, state_after_grant_rules_evaluation);
    }

    return grant_bind_request(block, &request);
}

int register_gatekeeper(Slapi_PBlock* block)
{
    if (slapi_pblock_get(block, SLAPI_PLUGIN_IDENTITY, plugin_id) != 0)
    {
        return report_plugin_registration_failure("Failed at getting plugin identity.");
    }

    if (slapi_pblock_set(block, SLAPI_PLUGIN_VERSION, SLAPI_PLUGIN_VERSION_03) != 0)
    {
        return report_plugin_registration_failure("Failed at setting LDAP protocol version.");
    }

    if (slapi_pblock_set(block, SLAPI_PLUGIN_DESCRIPTION, &plugin_desc) != 0)
    {
        return report_plugin_registration_failure("Failed at setting plugin description.");
    }

    if (slapi_pblock_set(block, SLAPI_PLUGIN_PRE_BIND_FN, on_bind_request) != 0)
    {
        return report_plugin_registration_failure("Failed at setting bind request handler.");
    }

    if (!set_aci_rules(block, grant_aci_rules, deny_aci_rules))
    {
        return report_plugin_registration_failure("Failed at setting custom ACI rules.");
    }

    return report_plugin_registration_success();
}
