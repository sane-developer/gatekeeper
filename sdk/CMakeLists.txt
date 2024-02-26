add_library(gatekeeper_sdk SHARED
    ./array.c
    ./string.c
    ./bind_request.c
    ./logging_policy.c
    ./policy_provider.c
)

target_include_directories(gatekeeper_sdk PUBLIC
    ../include
)
