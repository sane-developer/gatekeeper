file(GLOB plugin_files ./plugin.c ../sdk/ds_allocator.c ../sdk/ds_logger.c)

add_library(gatekeeper_plugin SHARED ${plugin_files})

target_include_directories(gatekeeper_plugin PUBLIC ../include)

target_link_libraries(gatekeeper_plugin gatekeeper_sdk)
