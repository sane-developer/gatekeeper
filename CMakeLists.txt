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
    ./include/aci_rule/
    ./include/bind_request/
    ./include/plugin_registration/
)

target_link_libraries(gatekeeper_sdk PUBLIC
    389ds
    ldap
    lber
    nss3
    smime3
    nssutil3
    sasl2
    ssl
    crypto
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
    gatekeeper_sdk
)

#
#  Builds the tests.
#

file(GLOB_RECURSE test_files
    ./tests/*.c
)

foreach(test_file ${test_files})
    get_filename_component(test_name ${test_file} NAME_WE)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE gatekeeper_sdk)
endforeach()
