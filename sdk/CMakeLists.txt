#
#  Define the plugin SDK and register its contents.
#

add_library(gatekeeper_sdk SHARED
    ./array/array.c
    ./string/string.c
    ./requests/bind_request.c
    ./providers/policy_provider.c
)
