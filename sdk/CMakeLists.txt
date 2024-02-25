#
#  Define the plugin SDK and register its contents.
#

add_library(gatekeeper_sdk SHARED
    array/array.c
    string/string.c
)

#
#  Include the public headers within the plugin SDK.
#

target_include_directories(gatekeeper_sdk BEFORE PUBLIC ../include)