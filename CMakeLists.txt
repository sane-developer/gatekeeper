#
# Setup basic CMake dependencies.
#

cmake_minimum_required(VERSION 3.20)

#
# Setup project metadata.
#

project(gatekeeper LANGUAGES C)

#
# Setup C standard.
#

set(CMAKE_C_STANDARD 11)

#
# Setup file crawling for LSP.
#

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# Setup directories for the output files.
#

set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR}/lib)

#
# Setup plugin api.
#

file(GLOB_RECURSE api_src_files ./src/*.c)

add_library(gatekeeper_sdk SHARED
    ${api_src_files}
)

target_include_directories(gatekeeper_sdk PUBLIC
    ./src/abstractions/
    ./src/enumerations/
    ./src/events/
    ./src/models/aci_rules/
    ./src/models/bind_requests/
    ./src/models/ldap_clients/
    ./src/models/ldap_connections/
    ./src/modules/
    /usr/include/dirsrv/
    /usr/include/nspr4/
)

target_link_libraries(gatekeeper_sdk PUBLIC
    -L/usr/lib64/dirsrv
    -lnspr4
)

#
# Setup plugin.
#

file(GLOB_RECURSE plugin_src_files ./src/plugin.c)

add_library(gatekeeper_plugin SHARED ${plugin_src_files})

target_link_libraries(gatekeeper_plugin PRIVATE gatekeeper_sdk)
