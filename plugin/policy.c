#include "plugin_registration.h"

typedef enum
{
    SUNDAY,

    MONDAY,

    TUESDAY,

    WEDNESDAY,

    THURSDAY,

    FRIDAY,

    SATURDAY
}
weekday_t;

static void skip_directory_manager_while_connecting_from_office(aci_rules_t* rules)
{
    configure_rule(rules, "skip directory manager while connecting from office");

        /* Applies to Directory Manager account */

        configure_apply_condition("directory manager");

            configure_operation(DN, STARTS_WITH, NOP);

                set_text_operand("cn=directory manager");

            register_operation();

        register_apply_condition();

        /* Triggers during connection that used static IP address (192.168.0.10) assigned to the administrator's desk */

        configure_trigger_condition("connecting from office");

            configure_operation(IP, EQUALS, NOP);

                set_integer_operand(3232235530);

            register_operation();

        register_trigger_condition();

    register_rule();
}

static void everyone_after_working_hours_except_managers(aci_rules_t* rules)
{
    configure_rule(rules, "everyone after working hours except managers");

        /* Excludes users who belong to 'managers' group */

        configure_exclude_condition("managers and assistants");

            configure_operation(GROUPS, ANY, NOP);

                set_text_operand("manager");

                set_text_operand("manager-assistant");

            register_operation();

        register_exclude_condition();

        /* Applies to every user */

        configure_apply_condition("everyone");

            configure_operation(DN, ENDS_WITH, OR);

                set_text_operand("cn=org,cn=pl");

            register_operation();

            configure_operation(DN, ENDS_WITH, NOP);

                set_text_operand("cn=org,cn=pl");

            register_operation();

        register_apply_condition();

        /* Triggers during working hours (7:00 - 17:00) from monday to friday */

        configure_trigger_condition("during working hours");

            configure_operation(TIME, BETWEEN, NOP);

                set_integer_operand(700);

                set_integer_operand(1700);

            register_operation();

        register_trigger_condition();

        configure_trigger_condition("from monday to friday");

            configure_operation(WEEKDAY, BETWEEN, NOP);

                set_integer_operand(MONDAY);

                set_integer_operand(FRIDAY);

            register_operation();

        register_trigger_condition();

    register_rule();
}

bool has_resolved_plugin_bind_policy(Slapi_PBlock* block, bind_policy_t* policy)
{
    /* Special ACI rules */

    skip_directory_manager_while_connecting_from_office(&policy->special);

    /* Deny ACI rules */

    everyone_after_working_hours_except_managers(&policy->deny);

    /* Grant ACI rules */

    return true;
}
