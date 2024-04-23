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

file(GLOB_RECURSE api_src_files api/*.c)

add_library(gatekeeper_sdk SHARED
    ${api_src_files}
)

target_include_directories(gatekeeper_sdk PUBLIC
    /usr/include/dirsrv
    /usr/include/nspr
    ./api/
)

target_link_libraries(gatekeeper_sdk PUBLIC
    -L/usr/lib64/dirsrv
#    -lslapd
    -lnspr4
)

#
# Setup plugin.
#

file(GLOB_RECURSE plugin_src_files plugin/*.c)

add_library(gatekeeper_plugin SHARED ${plugin_src_files})

target_link_libraries(gatekeeper_plugin PRIVATE gatekeeper_sdk)
