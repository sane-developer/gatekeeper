#
#  Define the plugin library and register its contents.
#

file(GLOB utilities
    ../sdk/allocators/ds_allocator.c
    ../sdk/loggers/ds_logger.c
)

add_library(gatekeeper_plugin SHARED
    ./plugin/plugin.c
    ${utilities}
)

#
#  Link the SDK with the plugin library.
#

target_link_libraries(gatekeeper_plugin gatekeeper_sdk)
