#
#  Setup basic CMake dependencies.
#

cmake_minimum_required(VERSION 3.20)

#
#  Setup project metadata.
#

project(gatekeeper LANGUAGES C)

#
#  Setup C standard.
#

set(CMAKE_C_STANDARD 11)

#
#  Setup file crawling for LSP.
#

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
#  Setup directories for the output files.
#

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

#
#  Setup std lib utilities.
#

file(GLOB std_utils
    ./sdk/std_logger.c
    ./sdk/std_allocator.c
)

file(GLOB ds_utils
    ./sdk/ds_logger.c
    ./sdk/ds_allocator.c
)

#
#  Setup plugin SDK.
#

file(GLOB sdk_files 
    ./sdk/array.c
    ./sdk/string.c
    ./sdk/bind_request.c
    ./sdk/binding_policy.c
    ./sdk/logging_policy.c
    ./sdk/policy_provider.c
)

add_library(gatekeeper_sdk SHARED ${sdk_files})

target_include_directories(gatekeeper_sdk PUBLIC ./include)

#
#  Setup plugin.
#

file(GLOB plugin_files ./src/*.c)

add_library(gatekeeper_plugin SHARED ${plugin_files} ${ds_utils})

target_link_libraries(gatekeeper_plugin gatekeeper_sdk)

target_include_directories(gatekeeper_plugin PUBLIC ./include)
