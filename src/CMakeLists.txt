#
#  Define the plugin library and register its contents.
#

add_library(gatekeeper_plugin SHARED
    ./plugin/plugin.c
    ./plugin/plugin.h
    ../sdk/allocators/ds_allocator.c
    ../sdk/loggers/ds_logger.c
)

#
#  Link the SDK with the plugin library.
#

target_link_libraries(gatekeeper_plugin gatekeeper_sdk)

#
#  Include the public headers within the plugin library.
#

target_include_directories(gatekeeper_plugin BEFORE PUBLIC ../include)