#
#  Global CMake configuration.
#

cmake_minimum_required(VERSION 3.20)

project(gatekeeper LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

#
#  Builds the SDK.
#

file(GLOB_RECURSE sdk_files
    ./lib/*.c
)

add_library(gatekeeper_sdk SHARED
    ${sdk_files}
)

target_include_directories(gatekeeper_sdk PUBLIC
    ./lib/
    ./lib/abstractions/
    ./lib/models/
    ./lib/models/rule/
    ./lib/models/status/
)

target_link_libraries(gatekeeper_sdk PUBLIC
    -L/usr/lib64/dirsrv
    -lnspr4
)

#
#  Builds the third party components.
#

file(GLOB_RECURSE third_party_files
    ./user/*.c
)

add_library(gatekeeper_third_party SHARED
    ${third_party_files}
)

target_link_libraries(gatekeeper_third_party PUBLIC
    gatekeeper_sdk
)

#
#  Builds the plugin.
#

file(GLOB_RECURSE plugin_files
    ./src/*.c
)

add_library(gatekeeper_plugin SHARED
    ${plugin_files}
)

target_link_libraries(gatekeeper_plugin PRIVATE
    gatekeeper_third_party
)