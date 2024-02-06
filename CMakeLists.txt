### Metadata

cmake_minimum_required(VERSION 3.22)

project(gatekeeper C)

set(CMAKE_C_STANDARD 11)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

### Files

file(GLOB STD_UTILITY_FILES
    ./src/allocators/std_allocator.c
    ./src/loggers/std_logger.c
)

file(GLOB SLAPI_UTILITY_FILES
    ./src/allocators/slapi_allocator.c
    ./src/loggers/slapi_logger.c
)

file(GLOB SDK_FILES
    ./src/models/*.c
    ./src/utilities/*.c
    ./src/validators/*.c
)

file(GLOB PLUGIN_FILES
    ./src/plugin.c
)

file(GLOB XF_PARSERS_FILES
    ./src/parsers/xf/xf_binding_policy_parser.c
    ./src/parsers/xf/xf_logging_policy_parser.c
)

file(GLOB XF_TOOLS_FILES
    ./tools/xf_binding_policy_evaluator.c
    ./tools/xf_logging_policy_evaluator.c
)

### SDK

add_library(gatekeeper_sdk SHARED ${SDK_FILES})

### Plugin

add_library(gatekeeper_plugin SHARED ${PLUGIN_FILES} ${SLAPI_UTILITY_FILES})
target_link_libraries(gatekeeper_plugin gatekeeper_sdk)

### Tools

foreach(XF_TOOL_FILE ${XF_TOOLS_FILES})
    get_filename_component(TOOL_NAME ${XF_TOOL_FILE} NAME_WE)
    add_executable(${TOOL_NAME} ${XF_TOOL_FILE} ${XF_PARSERS_FILES} ${STD_UTILITY_FILES})
#    target_compile_options(${TOOL_NAME} PRIVATE -DDISABLE_LOGGING)
    target_link_libraries(${TOOL_NAME} gatekeeper_sdk)
endforeach()