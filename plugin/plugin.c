#include <dirsrv/slapi-plugin.h>

int satisfies_grant_aci_rules(bind_request_t* request);

int satisfies_deny_aci_rules(bind_request_t* request);

int on_bind_request(Slapi_PBlock* block)
{
    bind_request_t request = {0};

    if (!setup_bind_request(block, &request))
    {
        return deny_bind_request(&request);
    }
    
    if (!satisfies_deny_aci_rules(&request))
    {
        return deny_bind_request(&request);
    }
    
    if (!satisfies_grant_aci_rules(&request))
    {
        return deny_bind_request(&request);
    }

    return grant_bind_request(&request);
}
